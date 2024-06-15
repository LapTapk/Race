#include "components/movement.hpp"
#include "game.hpp"
#include "components/transform.hpp"
#include <iostream>
#include <cmath>

Movement::Movement(GameObject* go) :
    Component(go) {}

void Movement::update() {
    float delta_time{ Game::instance->get_delta_time() };
    sf::Vector2f delta{ vector * delta_time };
    go->transform->position += delta;
}

void Movement::set_vector(sf::Vector2f dir, float speed) {
    if (dir.x == 0 && dir.y == 0) {
        vector = sf::Vector2f{ 0, 0 };
        return;
    }

    float len{ sqrt(dir.x * dir.x + dir.y * dir.y) };
    dir /= len;
    
    vector = dir * speed;
}
