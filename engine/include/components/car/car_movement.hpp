#ifndef CAR_MOVEMENT_HPP
#define CAR_MOVEMENT_HPP

#include "game_object.hpp"
#include "components/force.hpp"
#include "components/car/car_conf.hpp"
#include "components/road_check.hpp"
#include <SFML/Graphics.hpp>

/**
 * Компонент, отвеючащий за движение, схожее
 * с движением автомобиля
 */
class CarMovement : public Force {
private:
    sf::Vector2f* vdeceleration;///< Указатель на замедляющй вектор, само значение лежит в accelerations
    sf::Vector2f* vacceleration;///< Указатель на ускоряющий вектор, само значение лежит в accelerations
    sf::Vector2f direction;///< Направление движения

public:
    /**
     * Конструктор CarMovement
     * 
     * @param go Родительский объект
     * @param conf Конфигурация машины
     * @param checker Элемент, проверяющий нахождение на дороге
     */
    CarMovement(GameObject* go, CarConf conf, 
        RoadCheck* checker);
    CarConf conf;///< Конфигурация машины
    bool decelerate{ false };///< Состояния, показывающее, необходимо ли замедлять машину
    bool move{ false };///< Состояние, показывающее, необходимо ли начать движение
    void set_dir(sf::Vector2f dir);///< Задать направление движения. Нормализует выданный вектор
    sf::Vector2f get_dir();///< Получить вектор движения
    /**
     * Функция обработки кадра
     */
    void update() override;
    RoadCheck* checker;///< Элемент, проверяющий нахождение на дороге
};

#endif