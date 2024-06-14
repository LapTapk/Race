#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "game.hpp"

struct GameMock : Game {
    GameMock() : Game{
        GameConf{"../configs/test_conf.json"},
        new GameObject(nullptr),
        new Camera(scene.get(), 10)
    } { }
};