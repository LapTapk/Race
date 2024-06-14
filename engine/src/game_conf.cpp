#include "game_conf.hpp"
#include <jsoncpp/json/json.h>
#include <fstream>

GameConf::GameConf(std::string path) {
    std::ifstream conf_cin(path);
    Json::Value conf;
    conf_cin >> conf;

    window_size = std::make_pair(conf["window_size"][0u].asInt()
        , conf["window_size"][1u].asInt());
    title = conf["title"].asString();
    fps = conf["fps"].asInt();
    wheel_rot_delta = conf["wheel_rot_delta"].asInt();
}