#include "components/checkpoints.hpp"
#include "utils.hpp"
#include <numeric>

Checkpoint::Checkpoint(sf::Vector2f a, sf::Vector2f b) :
    l{ a, b } {}

void Checkpoint::check_if_crossing(line& other) {
    if (crossed) {
        return;
    }
    crossed = l.are_intersecting(other);
}

LoopCounter::LoopCounter(GameObject* go,
    std::vector<sf::Vector2f> cp_coords, Transform* car_transform_c,
    float line_size_c, bool draw_car_line_c) :
    Component{ go }, car_transform{ car_transform_c },
    line_size{ line_size_c }, draw_car_line{ draw_car_line_c } {
    int size{ cp_coords.size() };
    for (int i = 0; i < size / 2 - 1 + size % 2; i++) {
        Checkpoint checkpoint{
            cp_coords[i * 2], cp_coords[i * 2 + 1] };
        checkpoints.push_back(checkpoint);
    }
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


    for (Checkpoint& c : checkpoints) {
        c.check_if_crossing(car_line);
    }

    int crossed{
        std::accumulate(checkpoints.begin(), checkpoints.end(),
            0, [](int& acc, Checkpoint& c) {return acc + c.crossed;})
    };

    if (!checkpoints.empty() && checkpoints.back().crossed &&
        crossed >= checkpoints.size() / 3.0f) {
        points += 1;
        for (Checkpoint& c : checkpoints) {
            c.crossed = false;
        }
    }
}