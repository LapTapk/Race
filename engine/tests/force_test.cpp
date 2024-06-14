#include <doctest.h>
#include "components/force.hpp"
#include "components/transform.hpp"
#include "components/movement.hpp"

TEST_CASE("Apllying force") {
    GameObject* go{ new GameObject{nullptr} };
    Force* force{ new Force{go} };
    force->accelerations.push_back({ 5, 0.7 });
    force->accelerations.push_back({ -1, 100 });
    force->accelerations.push_back({ 7, -5.2 });


    go->update();
    CHECK_EQ(force->vector, sf::Vector2f{ 11, 95.5 } *0.5f);
    go->update();
    CHECK_EQ(force->vector, sf::Vector2f{ 22, 191 } *0.5f);
}