#include "components/rotor.hpp"
#include "game.hpp"
#include "components/transform.hpp"
#include <SFML/Graphics.hpp>

Rotor::Rotor(GameObject* go) : Component(go) {}

float Rotor::get_rotation() {
    sf::RenderWindow& window{ Game::instance->window };
    int mposx{ sf::Mouse::getPosition(window).x };
    int center{ window.getSize().x / 2 };
    int wrd{ Game::instance->conf.wheel_rot_delta };
    int diff{ mposx - center };
    if (diff != 0) {
        diff = std::min(abs(diff), wrd) * abs(diff) / diff;
    }
    float coef{ 1.0f * diff / wrd };
    return 90 * coef;
}

void Rotor::update() {
    go->transform->rotation = get_rotation();
}