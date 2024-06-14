#ifndef ROAD_CHECK_HPP
#define ROAD_CHECK_HPP

#include "game_object.hpp"
#include "components/map_drawer.hpp"

class CarMovement;

/**
 * Класс, отвечающий за проверку
 * нахождения машины в пределах дороги.
 * Проверка осуществляется с помощью
 * проверки пересечения отрезков 
 * границ дороги и создаваемого данной сущностью
 * отрезка. Последний создается от позиции 
 * родительского объекта до машины.
 */
class RoadCheck : public Component {
public:
    /**
     * Конструктор RoadCheck
     * 
     * @param go Родительский объект
     * @param outborders Внутренние границы дороги
     * @param inborders Внешние границы дороги
     */
    RoadCheck(GameObject* go, 
        std::vector<sf::Vector2f>& outborders,
        std::vector<sf::Vector2f>& inborders);
    std::vector<sf::Vector2f>& outborders;///< Внутренние границы дороги
    std::vector<sf::Vector2f>& inborders;///< Внешние границы дороги

    /**
     * @returns Состояние, казывающее на то, находится ли машина на дороге 
     */
    bool is_on_road(CarMovement* mover);
};

#endif