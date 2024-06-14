#ifndef GAME_CONF_HPP
#define GAME_CONF_HPP

#include <string>

/**
 * Класс, отвечающий за хранение конфигурций игры.
 * Читает конфигурации из JSON-файла по пути conf_path 
*/
class GameConf {
public:
    /**
     * Конструктор GameConf
     * 
     * @param conf_path Путь до конфигураций игры
    */
    GameConf(std::string conf_path);
    std::pair<int, int> window_size;///< Размер окна
    std::string title;///< Заголовок окна
    int fps;///< FPS игры
    int wheel_rot_delta;///< Предел поворота руля
};

#endif