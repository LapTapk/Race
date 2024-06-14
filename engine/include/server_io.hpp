#ifndef SERVER_IO_HPP
#define SERVER_IO_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include "game_object.hpp"
#include "components/transform.hpp"

using boost::asio::ip::tcp;

class ServerIO  {
public:
    std::string port;
    boost::asio::io_context io_context;
    tcp::socket socket;
    std::string server_ip;
    std::thread* reader_thread;
    std::string reply{ "" };
    void read_from_server(tcp::socket& socket);
    ServerIO(std::string server_ip, std::string port);
    void send_message(std::string mes);
    ~ServerIO();
};

#endif