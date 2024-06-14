#ifndef MOVER_HPP
#define MOVER_HPP

#include <SFML/Graphics.hpp>
#include "game_object.hpp"

/**
 * Компонент, отвечающий за передвижение 
 * объекта в игровом пространстве посредством 
 * телепортации его на вектор vector
 */
class Movement : public Component {
public:
    /**
     * Функция обработки кадра
     */
    void update() override; 
    /**
     * Конструктор Movement
     * 
     * @param go Родительский объект
     */
    Movement(GameObject* go);
    sf::Vector2f vector{sf::Vector2f{0, 0}}; ///< Вектор передвижения в данном кадре
    /**
     * Функция установления vector.
     * Параметр dir приводится к единичному вектору
     * и умножается на speed
     * 
     * @param dir Вектор направления, необазятельно единичный
     * @param speed Длина вектора передвижения
     */
    void set_vector(sf::Vector2f dir, float speed);
};

#endif