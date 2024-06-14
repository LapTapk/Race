#ifndef WHEEL_CAR_INPUT_HPP
#define WHEEL_CAR_INPUT_HPP

#include "game_object.hpp"
#include "components/rotor.hpp"
#include "components/car/car_movement.hpp"

class WheelCarInput : public Component {
private:
    Rotor* rotor;
    CarMovement* mover;
public:
    WheelCarInput(GameObject* go, Rotor* rotor, CarMovement* mover);
    void update() override;
};

#endif