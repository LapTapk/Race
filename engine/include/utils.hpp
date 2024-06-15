/**
 * Файл утилит, исползуемых в разных частях проекта
*/
#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

/**
 * Структура линии, способная обрабатвать
 * пересечения с другими линиями.
*/
struct line {
    sf::Vector2f a, b;
    line(sf::Vector2f a_c, sf::Vector2f b_c);
    bool ccw(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    bool are_intersecting(line& other);
};

/**
 * Функция отрисовки линий по данным координатам в 
 * игровом пространстве
 * 
 * @param coords Координаты в игровом пространстве, по которым будут строиться линии
 * @param draw_mode В каком режиме рисовать линии
*/
void draw_lines(std::vector<sf::Vector2f>& coords,
    sf::PrimitiveType draw_mode);

/**
 * @returns Позиция мыши в игровом пространстве
*/
sf::Vector2f get_mpos();
/**
 * @returns Была ли нажата левая кнопка мыши
*/
bool called_left_click();

#endif