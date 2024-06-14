#include "server_io.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <SFML/Graphics.hpp>
#include <thread>

using boost::asio::ip::tcp;

void ServerIO::read_from_server(tcp::socket& socket) {
    try {
        char data[1024];
        for (;;) {
            boost::system::error_code error;
            std::size_t length = socket.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof) {
                break; 
            }
            else if (error) {
                throw boost::system::system_error(error); 
            }

            reply = std::string{ data };
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception in read thread: " << e.what() << "\n";
    }
}

ServerIO::ServerIO(std::string server_ip_c,
    std::string port_c) :
    server_ip{ server_ip_c }, port{ port_c },
    socket{ io_context },
    io_context{} {
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(server_ip, port);
    boost::asio::connect(socket, endpoints);
    reader_thread = new std::thread(
        &ServerIO::read_from_server, this, std::ref(socket)
    );
}

void ServerIO::send_message(std::string mes) {
    try {
        std::string message{ mes };
        boost::asio::write(socket, boost::asio::buffer(message));
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

ServerIO::~ServerIO() {
    socket.close();
    reader_thread->join();
}