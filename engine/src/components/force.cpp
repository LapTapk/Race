#include "components/force.hpp"
#include <numeric>
#include <cmath>

Force::Force(GameObject* go) :
    Movement{go} {}

void Force::update() {
    sf::Vector2f acc_sum{
        std::accumulate(accelerations.begin(),
        accelerations.end(),
        sf::Vector2f{0, 0})
    };

    vector += acc_sum;
    Movement::update();
}