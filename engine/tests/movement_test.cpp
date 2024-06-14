#include <doctest.h>
#include "game_object.hpp"
#include "components/movement.hpp"
#include "components/transform.hpp"

TEST_CASE("Applying movement") {
    GameObject* go{ new GameObject{nullptr} };
    Movement* mover{ new Movement{go} };
    mover->vector = { 1, 5 };

    go->update();
    CHECK_EQ(go->transform->global_pos(), sf::Vector2f{ 1, 5 });
    go->update();
    CHECK_EQ(go->transform->global_pos(), sf::Vector2f{ 2, 10 });
}

TEST_CASE("Setting zero vector via set_vector") {
    GameObject* go{ new GameObject{nullptr} };
    Movement* mover{ new Movement{go} };
    mover->set_vector({ 0, 0 }, 1);
    CHECK_EQ(mover->vector, sf::Vector2f{ 0, 0 });
    mover->set_vector({ 1, 3 }, 0);
    CHECK_EQ(mover->vector, sf::Vector2f{ 0, 0 });
}

TEST_CASE("Setting nonzero vector via set_vector") {
    GameObject* go{ new GameObject{nullptr} };
    Movement* mover{ new Movement{go} };
    mover->set_vector({ 1, 1 }, 5);
    CHECK_EQ(mover->vector, sf::Vector2f{ 5, 5 });
    mover->set_vector({0.6, 0.2}, 7);
    CHECK_EQ(mover->vector, sf::Vector2f{0.6 * 7, 0.2 * 7});
}