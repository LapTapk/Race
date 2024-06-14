#include "components/car/car_movement.hpp"
#include "components/transform.hpp"
#include <cmath>
#include <iostream>

CarMovement::CarMovement(GameObject* go, CarConf conf_c,
    RoadCheck* checker_c) :
    Force{ go }, conf{ conf_c },
    checker{ checker_c } {
    accelerations.push_back(sf::Vector2f{ 0, 0 });
    accelerations.push_back(sf::Vector2f{ 0, 0 });
    vacceleration = &accelerations[0];
    vdeceleration = &accelerations[1];
}


float len(sf::Vector2f v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f get_unit_v(sf::Vector2f v) {
    float l{ len(v) };
    if (l == 0) {
        return v;
    }
    return v / l;
}

void CarMovement::set_dir(sf::Vector2f dir) {
    direction = get_unit_v(dir);
}

sf::Vector2f CarMovement::get_dir() {
    return direction;
}

void CarMovement::update() {
    decelerate = !checker->is_on_road(this);

    if (len(vector) > 1) {
        go->transform->rotation += conf.rotation_delta * direction.x;
    }

    sf::Vector2f forward{ go->transform->forward() };
    vector = forward * len(vector);

    if (move) {
        *vacceleration = forward * conf.acceleration;
    }
    else {
        *vacceleration = sf::Vector2f{ 0, 0 };
    }

    float ms{ conf.max_speed };
    if (decelerate) {
        *vacceleration *= conf.decelerate_coef;
        ms *= conf.decelerate_coef;
    }

    *vdeceleration =
        conf.friction * get_unit_v(-vector);
    if (len(vector) >= ms) {
        *vdeceleration += -*vacceleration;
    }
    this->Force::update();
}
