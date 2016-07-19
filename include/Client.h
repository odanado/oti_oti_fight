/*
 * Copyright (C) 2016 odanado
 * Licensed under the MIT License.
 */

#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "Timer.h"

#ifndef INCLUDE_CLIENT_H_
#define INCLUDE_CLIENT_H_
namespace oti_oti_fight {
class GameScene;
namespace asio = boost::asio;
using boost::asio::ip::udp;
class Client {
    udp::socket socket_;
    boost::array<char, 512> recvBuffer;
    udp::endpoint remoteEndpoint;
    GameScene *gameScene;
    int id;

 public:
    explicit Client(asio::io_service *ioService);
    void setGameScene(GameScene *gameScene) { this->gameScene = gameScene; }
    void join();
    void move(int id, const std::string &act);

 private:
    void startReceive();
    void handleReceive(const boost::system::error_code &error, std::size_t len);
    void send(const udp::endpoint &endpoint, const std::string &msg);
    void handleSend(boost::shared_ptr<std::string> /*message*/,
                    const boost::system::error_code & /*error*/,
                    std::size_t /*bytes_transferred*/) {}
};
}  // namespace oti_oti_fight
#endif  // INCLUDE_CLIENT_H_
