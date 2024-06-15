#include "components/checkpoints.hpp"
#include "utils.hpp"
#include <string>
#include <numeric>
#include <iostream>

Checkpoint::Checkpoint(sf::Vector2f a, sf::Vector2f b) :
    l{ a, b } {}

bool Checkpoint::check_if_crossing(line& other) {
    if (crossed) {
        return crossed;
    }
    return l.are_intersecting(other);
}

LoopCounter::LoopCounter(GameObject* go,
    std::vector<sf::Vector2f> cp_coords, Transform* car_transform_c,
    float line_size_c, bool draw_car_line_c, TextRenderer* rend_c) :
    Component{ go }, car_transform{ car_transform_c },
    line_size{ line_size_c }, draw_car_line{ draw_car_line_c },
    rend{ rend_c } {
    int size{ cp_coords.size() };
    for (int i = 0; i < size / 2 - 1 + size % 2; i++) {
        Checkpoint checkpoint{
            cp_coords[i * 2], cp_coords[i * 2 + 1] };
        checkpoints.push_back(checkpoint);
    }

    rend->text.setFillColor(sf::Color{255, 255, 255});
}

void LoopCounter::update() {
    sf::Vector2 forward{ car_transform->forward() };
    forward *= line_size / 2;
    line car_line{ forward + car_transform->global_pos(),
         -forward + car_transform->global_pos() };

    if (draw_car_line) {
        std::vector<sf::Vector2f> car_points{ car_line.a, car_line.b };
        draw_lines(car_points, sf::Lines);
    }


    for (int i = 0; i < checkpoints.size() - 1; i++) {
        checkpoints[i].crossed = checkpoints[i].check_if_crossing(car_line);
    }

    int crossed{
        std::accumulate(checkpoints.begin(), checkpoints.end(),
            0, [](int& acc, Checkpoint& c) {return acc + c.crossed;})
    };

    if (!checkpoints.empty() &&
        crossed >= checkpoints.size() / 3.0f &&
        checkpoints.back().check_if_crossing(car_line)) {
        points += 1;
        for (Checkpoint& c : checkpoints) {
            c.crossed = false;
        }
    }

    rend->text.setString(std::to_string(points));
}