#include "components/map_drawer.hpp"
#include "components/transform.hpp"
#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "utils.hpp"
#include "game.hpp"

MapCoords::MapCoords(std::string path_to_json_c) :
    path_to_json(path_to_json_c) {
    std::ifstream fin{ path_to_json };
    Json::Value json;
    fin >> json;
    for (Json::Value& v : json["points"]) {
        points.push_back({ v[0].asFloat(), v[1].asFloat() });
    }
    if (!points.empty()) {
        points.push_back(points[0]);
    }
}

Json::Value MapCoords::to_json() {
    Json::Value pts;
    Json::Value vec{ Json::arrayValue };
    for (sf::Vector2f& p : points) {
        Json::Value json_p{ Json::arrayValue };
        json_p.append(p.x);
        json_p.append(p.y);
        vec.append(json_p);
    }
    pts["points"] = vec;
    return pts;
}

void MapCoords::save() {
    std::ofstream fout
    { path_to_json, std::ofstream::out | std::ofstream::trunc };
    fout << to_json();
}

void MapCoords::push_back(sf::Vector2f v) {
    if (!points.empty()) {
        points.pop_back();
    }
    points.push_back(v);
    points.push_back(points[0]);
}

MapCoords::~MapCoords() {
    save();
}

MapDrawer::MapDrawer(GameObject* go, std::string path_to_json,
    bool write_c, sf::PrimitiveType draw_mode_c) :
    Component{ go }, coords{ path_to_json }, write{ write_c },
    draw_mode{ draw_mode_c } {
}

void MapDrawer::update() {
    if (write && called_left_click()) {
        coords.push_back(get_mpos());
        coords.save();
    }

    draw_lines(coords.points, draw_mode);
}