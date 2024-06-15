#include "components/camera.hpp"

Camera::Camera(GameObject* go, float zoomout_c) :
    Component(go), zoomout(zoomout_c) {}