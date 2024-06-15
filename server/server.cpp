#include <iostream>
#include <memory>
#include <thread>
#include <set>
#include <mutex>
#include <boost/asio.hpp>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "server.hpp"
using boost::asio::ip::tcp;

player::player(std::shared_ptr<tcp::socket> socket, int number) : socket_(socket), number_(number), is_ready_{false}{}
std::vector<player>::iterator find_player_by_socket(
    std::shared_ptr<tcp::socket> &s)
{
    auto p{
        [&s](player pl)
        {
            return pl.socket_ == s;
        }};
    auto player{std::find_if(
        players.begin(), players.end(), p)};
    return player;
}

void handle_client(std::shared_ptr<tcp::socket> socket)
{
    try
    {
        char data[1024];
        for (;;)
        {
            std::size_t length = socket->read_some(
                boost::asio::buffer(data));

            player &sender{*find_player_by_socket(socket)};
            int num{sender.number_};
            bool are_all_ready{true};
            if (boost::trim_right_copy(std::string{data}) == "ready")
            {
                sender.is_ready_ = true;
                for (auto &player : players)
                {
                    if (player.is_ready_ == false)
                    {
                        are_all_ready = false;
                    }
                }
                if (are_all_ready)
                {
                    are_all_ready = false;

                    std::lock_guard<std::mutex> lock(clients_mutex);
                    for (auto &player : players)
                    {
                        player.is_ready_ = false;
                        std::string mes{
                            std::to_string(players.size()) +
                            " " + std::to_string(player.number_)};
                        boost::asio::write(*player.socket_,
                                           boost::asio::buffer(mes));
                    }
                }
            }
            else if (length > 0)
            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                for (auto &player : players)
                {
                    if (player.socket_ == socket)
                    {
                        continue;
                    }

                    std::string mes{
                        std::to_string(num) +
                        " " + data};

                    std::cout << mes << std::endl;
                    boost::asio::write(*player.socket_,
                                       boost::asio::buffer(mes));
                }
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
        std::lock_guard<std::mutex> lock(clients_mutex);
        players.erase(find_player_by_socket(socket));
    }
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: sync_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::atoi(argv[1])));
        int number = 1;
        for (;;)
        {
            auto socket = std::make_shared<tcp::socket>(io_context);
            acceptor.accept(*socket);

            players.push_back(player(socket, number));
            std::cout << "new client connected" << std::endl;
            number++;

            std::thread(handle_client, socket).detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
