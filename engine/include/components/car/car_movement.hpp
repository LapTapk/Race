#ifndef CAR_MOVEMENT_HPP
#define CAR_MOVEMENT_HPP

#include "game_object.hpp"
#include "components/force.hpp"
#include "components/car/car_conf.hpp"
#include "components/road_check.hpp"
#include <SFML/Graphics.hpp>

class CarMovement : public Force {
private:
    sf::Vector2f* vdeceleration, * vacceleration;
    sf::Vector2f direction;

public:
    CarMovement(GameObject* go, CarConf conf, 
        RoadCheck* checker);
    CarConf conf;
    bool decelerate{ false }, move{ false };
    void set_dir(sf::Vector2f dir);
    sf::Vector2f get_dir();
    void update() override;
    RoadCheck* checker;
};

#endif