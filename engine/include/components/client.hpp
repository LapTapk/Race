#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include "game_object.hpp"
#include "components/transform.hpp"
#include "server_io.hpp"

using boost::asio::ip::tcp;

class Client : public Component {
public:
    ServerIO& sio;
    std::vector<sf::Vector2f> coords;
    std::vector<GameObject*> players;
    int this_ind;
    std::string create_mes();
    void parse_coords(
        std::string mes);
    Client(GameObject* go, ServerIO& sio,
        int this_ind, std::vector<GameObject*> players);
    void set_positions();
    void update() override;
};

#endif