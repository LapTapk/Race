#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "game_object.hpp"

/**
 * Компонент камеры
 */
class Camera : public Component {
public:
    /**
     * Конструктор Camera
     * 
     * @param go Родительский объект
     * @param zoomout Коэффициент отдаления камеры от сцены
     */
    Camera(GameObject* go, float zoomout = 1);
    float zoomout;///< Коэффициент отдаления камеры от сцены 
};

#endif