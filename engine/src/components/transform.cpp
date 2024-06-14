#include "game_object.hpp"
#include "game.hpp"
#include "components/transform.hpp"
#include <cmath>

Transform::Transform(GameObject* go) : Component(go) {}

sf::Vector2f Transform::forward() {
    float angle{ global_rot() / 180.0f * M_PI };
    return sf::Vector2f{ sin(angle), cos(angle) };
}

sf::Vector2f Transform::global_pos() {
    GameObject* parent{ go->parent };
    if (parent == nullptr) {
        return position;
    }

    float angle{ -parent->transform->global_rot() / 180.0f * M_PI };
    sf::Vector2f rot_pos{
        position.x * cos(angle) - position.y * sin(angle),
        position.y * cos(angle) + position.x * sin(angle)
    };
    sf::Vector2f parent_gpos{ parent->transform->global_pos() };
    return rot_pos + parent_gpos;
}

sf::Vector2f Transform::global_scale() {
    GameObject* parent{ go->parent };
    if (parent == nullptr) {
        return scale;
    }

    sf::Vector2f parent_gscale = parent->transform->global_scale();
    return sf::Vector2f(scale.x * parent_gscale.x, scale.y * parent_gscale.y);
}

float Transform::global_rot() {
    GameObject* parent{ go->parent };
    if (parent == nullptr) {
        return rotation;
    }

    float parent_grot = parent->transform->global_rot();
    return rotation + parent_grot;
}