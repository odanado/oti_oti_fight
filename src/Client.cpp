/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */
#include <string>
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>

#include "Client.h"
#include "NCursesUtil.h"
#include "GameScene.h"

namespace oti_oti_fight {
Client::Client(asio::io_service *ioService) : socket_(*ioService) {
    socket_.open(udp::v4());
    remoteEndpoint =
        udp::endpoint(asio::ip::address::from_string("127.0.0.1"), 50000);
    startReceive();
}

void Client::startReceive() {
    socket_.async_receive_from(
        asio::buffer(recvBuffer), remoteEndpoint,
        boost::bind(&Client::handleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}
void Client::handleReceive(const boost::system::error_code &error,
                           std::size_t len) {
    std::string msg(recvBuffer.data(), len);

    std::vector<std::string> recvData;
    boost::split(recvData, msg, boost::is_space());
    if (recvData.front() == "ok") {
        id = std::stoi(recvData[1].c_str());
    } else if (recvData.front() == "start") {
        auto time = std::stoll(recvData[1]);
        auto num = std::stoi(recvData[2]);
        std::vector<int> xs, ys;
        for (int i = 0; i < num; i++) {
            xs.push_back(std::stoi(recvData[i + 3]));
            ys.push_back(std::stoi(recvData[i + num + 3]));
        }

        gameScene->start(Timer::milliseconds(time), xs, ys);
    } else if (recvData.front() == "move") {
        auto id = std::stoi(recvData[1]);
        auto act = recvData[2];
        gameScene->move(id, act);
    }
    startReceive();
}

void Client::send(const udp::endpoint &endpoint, const std::string &msg) {
    auto message = boost::make_shared<std::string>(msg);
    socket_.async_send_to(
        boost::asio::buffer(*message), endpoint,
        boost::bind(&Client::handleSend, this, message,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void Client::join() { send(remoteEndpoint, "join"); }

void Client::move(int id, const std::string &act) {
    send(remoteEndpoint, "move " + std::to_string(id) + " " + act);
}
}  // namespace oti_oti_fight
