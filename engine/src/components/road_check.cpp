#include "components/road_check.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "components/transform.hpp"
#include "components/car/car_movement.hpp"
#include <cmath>
#include "utils.hpp"

RoadCheck::RoadCheck(GameObject* go,
    std::vector<sf::Vector2f>& outborders_c,
    std::vector<sf::Vector2f>& inborders_c) :
    Component{ go }, outborders{ outborders_c },
    inborders{ inborders_c } {}

void add_lines(std::vector<line>& lines,
    std::vector<sf::Vector2f>& borders) {
    for (int i = 0; i < borders.size() - 1; i++) {
        line l{ borders[i], borders[i + 1] };
        lines.push_back(l);
    }
}

bool RoadCheck::is_on_road(CarMovement* mover) {
    std::vector<line> lines;
    add_lines(lines, outborders);
    add_lines(lines, inborders);

    line check_line{
        go->transform->global_pos(),
        mover->go->transform->global_pos(),
    };

    int cnt{ 0 };
    for (line& l : lines) {
        if (check_line.are_intersecting(l)) {
            cnt++;
        }
    }

    return cnt % 2 != 0;
}