#include "event_manager.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>

void EventManager::update() {
    events.clear();
    sf::Event e;
    Game* game{ Game::instance };
    while(game->window.pollEvent(e)){
        events.push_back(e);
    }
}