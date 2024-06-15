#include "components/client.hpp"
#include <iostream>
#include <server_io.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include "game_object.hpp"
#include "components/transform.hpp"

using boost::asio::ip::tcp;

std::string Client::create_mes() {
    std::string res{ "" };
    sf::Vector2f pos{
        go->transform->position
    };

    std::string x{ std::to_string(pos.x) };
    std::string y{ std::to_string(pos.y) };
    res += x + " " + y;

    return res;
}


void Client::parse_coords(
    std::string mes) {
    std::string str;
    std::stringstream ss(mes);
    try {
        getline(ss, str, ' ');
        int ind{ stoi(str) };
        ind--;
        getline(ss, str, ' ');
        float x{ stof(str) };
        getline(ss, str, ' ');
        float y{ stof(str) };

        coords[ind] = { x, y };
    }
    catch (std::exception& e) {

    }
}


Client::Client(GameObject* go, ServerIO& sio_c,
    int this_ind_c, std::vector<GameObject*> players_c) :
    Component{ go }, sio{ sio_c },
    this_ind{ this_ind_c }, players{ players_c },
    coords{ players_c.size() } {}

void Client::set_positions() {
    for (int i = 0; i < players.size(); i++) {
        if (i == this_ind) {
            continue;
        }

        players[i]->transform->position = coords[i];
    }
}

void Client::update() {
    sio.send_message(create_mes());
    parse_coords(sio.reply);
    set_positions();
}