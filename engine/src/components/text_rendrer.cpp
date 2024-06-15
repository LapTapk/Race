#include "components/text_renderer.hpp"
#include "game.hpp"
#include "components/camera.hpp"
#include "components/transform.hpp"
#include <cmath>
#include <iostream>

TextRenderer::TextRenderer(GameObject* go, std::string path_to_font) :
    Component{ go } {
    font.loadFromFile(path_to_font);
    text.setFont(font);
}

float TextRenderer::rotation() {
    Game* game{ Game::instance };
    Camera* camera{ game->camera };
    Transform* transform{ go->transform };

    int camera_rot{ camera->go->transform->global_rot() };
    int rot{ transform->global_rot() - camera_rot };
    return rot;
}

sf::Vector2f TextRenderer::position() {
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

sf::Vector2f TextRenderer::scale() {
    Game* game{ Game::instance };
    Camera* camera{ game->camera };
    Transform* transform{ go->transform };

    sf::Vector2f scale{ transform->global_scale() };
    scale /= camera->zoomout;
    return scale;
}

void TextRenderer::update() {
    text.setRotation(rotation());
    text.setPosition(position());
    text.setScale(scale());

    Game* game{ Game::instance };
    game->window.draw(text);
}