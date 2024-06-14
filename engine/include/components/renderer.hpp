#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "game_object.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include "components/camera.hpp"

/**
 * Компонент, отвечающий за отрисовку спрайта 
 * SFML в игровом пространстве.
 * Осуществляет обработку спрайта в соотвествии с 
 * параметрами Transform
 */
class Renderer : public Component {
public:
    /**
     * Конструктор Renderer
     * 
     * @param go Родительский объект
     * @param path_to_img Путь до изображения спрайта
     */
    Renderer(GameObject* go, std::string path_to_img);
    /**
     * Функция обработки кадра
     */
    void update() override;
    float rotation();
    sf::Vector2f position();
    sf::Vector2f scale();
    Camera* camera;
private:
    sf::Sprite sprite;///< Отрисовываемый спрайт
    sf::Texture texture;///< Текстура отрисовываемого спрайта
};

#endif