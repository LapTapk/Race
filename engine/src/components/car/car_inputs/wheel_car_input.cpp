#include "components/car/car_inputs/wheel_car_input.hpp"
#include "game.hpp"
#include "event_manager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

WheelCarInput::WheelCarInput(GameObject* go, Rotor* rotor_c,
    CarMovement* mover_c) :
    Component{ go }, rotor{ rotor_c }, mover{ mover_c } {}

void WheelCarInput::update() {
    float angle{ (90 - rotor->get_rotation()) / 180.0f * M_PI };
    sf::Vector2f dir{ cos(angle), sin(angle) };
    mover->set_dir(dir);

    EventManager& em{ Game::instance->event_manager };
    mover->move = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}