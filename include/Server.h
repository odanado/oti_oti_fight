/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <iostream>
#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>

#include "Timer.h"
#include "NCursesUtil.h"

#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_
namespace oti_oti_fight {
namespace asio = boost::asio;
using boost::asio::ip::udp;

class Server {
    udp::socket socket_;
    boost::array<char, 512> recvBuffer;
    udp::endpoint remoteEndpoint;
    int id;
    std::vector<udp::endpoint> joinEndpoint;

 public:
    Server(asio::io_service* io_service, int port);

 private:
    void startReceive();
    void handleReceive(const boost::system::error_code& error, std::size_t len);

    void sendOK(const udp::endpoint& endpoint, int id) {
        send(endpoint, "ok " + std::to_string(id));
    }

    void sendStart() {
        auto time =
            Timer::now<Timer::milliseconds>() + Timer::milliseconds(1000);
        std::string msg = "start ";
        msg += std::to_string(time.count()) + " ";
        msg += std::to_string(id) + std::string(" ");
        msg += "1 6 ";
        msg += "1 6";
        broadcast(msg);
    }

    void broadcast(const std::string& msg) {
        for (const auto& endpoint : joinEndpoint) {
            send(endpoint, msg);
        }
    }

    void send(const udp::endpoint& endpoint, const std::string& msg);

    void handleSend(boost::shared_ptr<std::string> /*message*/,
                    const boost::system::error_code& /*error*/,
                    std::size_t /*bytes_transferred*/) {}
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_SERVER_H_
