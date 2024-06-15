#ifndef FORCE_HPP
#define FORCE_HPP

#include "game_object.hpp"
#include "movement.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Компонент, прилагающий силу к объекту по формуле.
 * Масса объекта не учитывается, только данное ускорение.
 */
class Force : public Movement {
public:
    std::vector<sf::Vector2f> accelerations;///< Список ускорений
    /**
     * Конструктор Force
     * 
     * @param go Родительский объект
     * @param mover Mover объекта
     */
    Force(GameObject* go);
    /**
     * Функция счета кадра
     */
    void update() override;
};

#endif