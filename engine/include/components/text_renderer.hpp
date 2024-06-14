#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include "game_object.hpp"
#include <string>
#include <SFML/Graphics.hpp>

/**
 * Компонент, отображающий текст
 */
class TextRenderer : public Component {
public: 
    sf::Font font;///< Шрифт текста
    sf::Text text;///< Текст
    /**
     * Конструктор TextRenderer 
     * 
     * @param go Родительский объект
     * @param path_to_font Путь до шрифта
     */
    TextRenderer(GameObject* go, std::string path_to_font);
    /**
     * Ориентация текста
     */
    float rotation(); 
    /**
     * Позиция текста
     */
    sf::Vector2f position();
    /**
     * Размер текста
     */
    sf::Vector2f scale();
    /**
     * Функция обработки кадров
     */
    void update() override;
};

#endif