/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */
#include <string>
#include <vector>

#include "Server.h"
namespace oti_oti_fight {
Server::Server(asio::io_service *ioService, int port)
    : socket_(*ioService, udp::endpoint(udp::v4(), port)), id(0) {
    startReceive();
}
void Server::startReceive() {
    socket_.async_receive_from(
        asio::buffer(recvBuffer), remoteEndpoint,
        boost::bind(&Server::handleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}
void Server::handleReceive(const boost::system::error_code &error,
                           std::size_t len) {
    std::string msg(recvBuffer.data(), len);

    std::vector<std::string> recvData;
    boost::split(recvData, msg, boost::is_space());
    if (recvData.front() == "join") {
        if (id != 4) {
            joinEndpoint.emplace_back(remoteEndpoint);
            id++;
            sendOK(remoteEndpoint, id);
            if (id == 4) {
                sendStart();
            }
        }
    } else if (recvData.front() == "move") {
        broadcast(msg);
    }
    startReceive();
}

void Server::send(const udp::endpoint &endpoint, const std::string &msg) {
    auto message = boost::make_shared<std::string>(msg);
    socket_.async_send_to(
        boost::asio::buffer(*message), endpoint,
        boost::bind(&Server::handleSend, this, message,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}
}  // namespace oti_oti_fight
