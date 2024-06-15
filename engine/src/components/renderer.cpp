#include "components/renderer.hpp"
#include <iostream>
#include "components/transform.hpp"
#include "game.hpp"
#include <cmath>

Renderer::Renderer(GameObject* go,
    std::string path_to_img) :
    Component{ go } {
    texture.loadFromFile(path_to_img);
    sprite.setTexture(texture);
    sf::Vector2f tzise{ texture.getSize() };
    sprite.setOrigin(tzise.x / 2, tzise.y / 2);
}

float Renderer::rotation() {
    Game* game{ Game::instance };
    Camera* camera{ game->camera };
    Transform* transform{ go->transform };

    int camera_rot{ camera->go->transform->global_rot() };
    int rot{ transform->global_rot() - camera_rot };
    return rot;
}

sf::Vector2f Renderer::position() {
    Game* game{ Game::instance };
    Camera* camera{ game->camera };
    Transform* transform{ go->transform };
    int camera_rot{ camera->go->transform->global_rot() };
    sf::Vector2f pos{ transform->global_pos() };

    sf::Vector2f camera_pos{ camera->go->transform->global_pos() };

    sf::Vector2f radius{ pos - camera_pos };
    radius /= camera->zoomout;
    double alpha = camera_rot / 180.0f * M_PI;
    sf::Vector2f rot_pos{ radius.x * cos(alpha) - radius.y * sin(alpha),
        radius.y * cos(alpha) + radius.x * sin(alpha) };
    rot_pos.y *= -1;

    sf::Vector2f window_offset(
        game->conf.window_size.first / 2, game->conf.window_size.second / 2);

    rot_pos += window_offset;
    return rot_pos;
}

sf::Vector2f Renderer::scale() {
    Game* game{ Game::instance };
    Camera* camera{ game->camera };
    Transform* transform{ go->transform };

    sf::Vector2f scale{ transform->global_scale() };
    scale /= camera->zoomout;
    return scale;
}

void Renderer::update() {
    sprite.setRotation(rotation());
    sprite.setPosition(position());
    sprite.setScale(scale());

    Game* game{ Game::instance };
    game->window.draw(sprite);
}
