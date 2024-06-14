#ifndef ROTOR_HPP
#define ROTOR_HPP

#include "game_object.hpp"

/**
 * Компонент, отвечащий за
 * вращение обеъекта в зависимости 
 * от позиции мыши
 */
class Rotor : public Component {
public:
    /**
     * Конструктор Rotor
     * 
     * @param go Родительский объект
     */
    Rotor(GameObject* go);
    /**
     * @returns Ориентация в зависимости от позиции мыши
     */
    float get_rotation();
    /**
     * Функция обработки кадра
     */
    void update() override;
};

#endif