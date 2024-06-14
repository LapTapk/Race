#ifndef SERVER_HPP
#define SERVER_HPP
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;

std::mutex clients_mutex;

struct player
{
    int number_;
    std::shared_ptr<tcp::socket> socket_;
    bool is_ready_;
    player(std::shared_ptr<tcp::socket> socket, int number);
};

std::vector<player> players;

std::vector<player>::iterator find_player_by_socket(
    std::shared_ptr<tcp::socket> &s);

void handle_client(std::shared_ptr<tcp::socket> socket);

#endif