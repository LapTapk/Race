#ifndef MAP_DRAWER_HPP
#define MAP_DRAWER_HPP

#include <string>
#include <vector>
#include "game_object.hpp"
#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>

/**
 * Класс, отвечающий за хранение информации
 * о координатах.
 * Способен записывать и читать координаты линий в JSON-файлах.
 */
class MapCoords {
public:
    /**
     * Конструктор MapCoords
     * 
     * @param path_to_json Путь до JSON-файла с координатами линий
     */
    MapCoords(std::string path_to_json);
    std::vector<sf::Vector2f> points;///< Координаты линий
    /**
     * Парсинг линий в JSON-формат
     * 
     * @returns Координаты линий в JSON-формате
    */ 
    Json::Value to_json();
    /**
     * Сохранение линий в JSON-файл
     */
    void save();
    /**
     * Добавление точки в points
     */
    void push_back(sf::Vector2f v);
    /**
     * Деструктор MapCoords. Записывает 
     * points в JSON-файл 
     */
    ~MapCoords();
private:
    std::string path_to_json;///< Путь до JSON файла
};

/**
 * Компонент, отрисовывающий точки на экране.
 * Способен добавлять точки в MapCoords по нажатию 
 * ЛКМ. Сохраняет точки при каждом добавлении.
 */
class MapDrawer : public Component {
public:
    /**
     * Конструктор MapDrawer
     * 
     * @param go Родительский объект
     * @param path_to_json Путь до JSON-файла с координатами линий
     * @param write Состояние, показывающее, нужно ли считывать точки по нажатию ЛКМ
     * @param draw_mode Параметр отрисовки линий
     */
    MapDrawer(GameObject* go,
        std::string path_to_json, bool write,
        sf::PrimitiveType draw_mode);
    /**
     * Функция счета кадра
     */
    void update() override;
    bool write;///< Состояние, показывающее, нужно ли считывать точки по нажатию ЛКМ
    MapCoords coords;///< MapCoords, откуда будут считываться линии
    /** 
     * Функция отрисовки линий
    */
    void draw();
    sf::PrimitiveType draw_mode;///< Параметр отрисовки линий
};

#endif