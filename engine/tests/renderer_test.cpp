#include <doctest.h>
#include "game.hpp"
#include "components/renderer.hpp"
#include "components/transform.hpp"
#include "components/camera.hpp"

TEST_CASE("Position") {
    GameObject* scene{ nullptr };
    Camera* cam{ new Camera{scene} };
    GameObject* go{ new GameObject{scene} };
    Renderer* rend{ new Renderer{go, "../assets/penguin.png"} };
    go->transform->position = { -5, 7 };

    sf::Vector2f actual{ rend->position() };
    sf::Vector2f right;
    CHECK_EQ(right, actual);
}