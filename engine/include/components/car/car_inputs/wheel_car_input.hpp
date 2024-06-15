#ifndef WHEEL_CAR_INPUT_HPP
#define WHEEL_CAR_INPUT_HPP

#include "game_object.hpp"
#include "components/rotor.hpp"
#include "components/car/car_movement.hpp"

/**
 * Компонент, передающий ввод 
 * в движок машин
 */
class WheelCarInput : public Component {
private:
    Rotor* rotor;///< Вращатель руля
    CarMovement* mover;///< Двигатель машины
public:
    /**
     * Конструктор WheelCarInput
     * 
     * @param go Родительский объект
     * @param rotor Вращатель руля
     * @param mover Двигатель машины
     */
    WheelCarInput(GameObject* go, Rotor* rotor, CarMovement* mover);
    /**
     * Функция обработки кадра
     */
    void update() override;
};

#endif