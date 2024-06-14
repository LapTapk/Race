#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <SFML/Graphics.hpp>

#include "game_object.hpp"

/**
 * Компонент, отвечающий за хранение и
 * вычисления информации о положении,
 * ориентации и размере в игровом пространстве
 */
class Transform : public Component {
public:
    sf::Vector2f position{sf::Vector2f(0, 0)};///< Позиция в пространстве относительно родительского объекта родительского объекта компонента
    sf::Vector2f global_pos();///< Позиция в пространстве относительно сцены
    sf::Vector2f scale = sf::Vector2f(1, 1);///< Размер относительно родительского объекта родительского объекта компонента
    sf::Vector2f global_scale();///< Размер относительно сцены
    float rotation = 0;///< Ориентация в градусах отсносительно родительского объекта родительского объекта компонента
    float global_rot();///< Ориентация относительно сцены
    /**
     * Конструктор Transform
     * 
     * @param go Родительский объект
     */
    Transform(GameObject* go);
    sf::Vector2f forward();///< Вектор в базисе, присущем компоненту Transform сцены, который соответствует вектору {0, 1} в локальном базисе
};

#endif