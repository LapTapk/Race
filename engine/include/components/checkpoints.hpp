#ifndef CHECKPOINTS_HPP
#define CHECKPOINTS_HPP

#include "game_object.hpp"
#include "components/map_drawer.hpp"
#include "components/transform.hpp"
#include <SFML/Graphics.hpp>
#include "utils.hpp"

/**
 * Структура, отвечающая за хранение информации
 * о контрольных линиях
 */
struct Checkpoint {
    bool crossed{ false };///< Состояние, показывающее, была ли пересечена линия
    line l;///< Контрольная линия
    /**
     * Конструктор Checkpoint
     * 
     * @param a Точка начала линии
     * @param b Точка конца линии
     */
    Checkpoint(sf::Vector2f a, sf::Vector2f b);

    /**
     * Функция, проверяющая, была ли пересечена линия
     * 
     * @param car Линия машины
     */
    void check_if_crossing(line& car);
};

/**
 * Компонент, отвечающий за подсчет пройденных кругов.
 * Рисует линию машины, с помощью которой будет 
 * осуществляться проверка пересения контрольных линий
 */
class LoopCounter : public Component {
private:
    std::vector<Checkpoint> checkpoints;///< Контольные линии
    Transform* car_transform;///< Transform машины
    float line_size;///< Длина линии машины
public:
    int points{ 0 };///< Количество очков
    bool draw_car_line;///< Состояние, которое будет определять, будет ли рисоваться на экране линия машины
    /**
     * Конструктор LoopCounter
     * 
     * @param go Родительский объект
     * @param checkpoint_coords Координаты начал и концов контрольных линий, начало и конец линии должны идти подряд
     * @param car_transform Tranform машины
     * @param line_size Длина линии машины
     * @param draw_car_line Состояние, которое будет определять, будет ли рисоваться на экране линия машиныe
     */
    LoopCounter(GameObject* go,
        std::vector<sf::Vector2f> checkpoint_coords,
        Transform* car_transform, float line_size,
        bool draw_car_line);
    /**
     * Функция счета кадра
     */
    void update() override;
};

#endif