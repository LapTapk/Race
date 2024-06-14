#ifndef DEFAULT_SCENE_HPP
#define DEFAULT_SCENE_HPP

#include "game_object.hpp"
#include "components.hpp"
#include <vector>
#include <string>

GameObject* create_penguin(GameObject* scene, Camera* camera) {
    GameObject* go{ new GameObject{scene} };
    Renderer* rend{ new Renderer{go, "../assets/penguin.png" } };
    go->transform->position = sf::Vector2f{ 1000, 1000 };
    return go;
}

GameObject* create_map_drawer(GameObject* scene, std::string path,
    bool write, sf::PrimitiveType draw_mode) {
    GameObject* go{ new GameObject{scene} };
    new MapDrawer{ go, path, write, draw_mode };
    return go;
}

std::tuple<GameObject*, CarMovement*> create_car(GameObject* scene, Camera* camera, RoadCheck* check) {
    GameObject* car{ new GameObject{scene} };
    CarConf car_conf{ 500, 30, 1, 1, 0.1 };
    CarMovement* car_mover{ new CarMovement{car, car_conf, check} };
    new Renderer{ car, "../assets/penguin.png" };
    car_mover->decelerate = false;
    return { car, car_mover };
}

std::vector<GameObject*> create_cars(GameObject* scene, int cnt,
    Camera*& camera, RoadCheck* check, int ind) {
    std::vector<GameObject*> res{ cnt };
    for (int i = 0; i < cnt; i++) {
        GameObject* car;
        CarMovement* mover;
        std::tie(car, mover) = create_car(scene, camera, check);
        res[i] = car;
        if (i == ind) {
            GameObject* camera_go{ new GameObject{car} };
            camera = new Camera{ camera_go, 10 };
            GameObject* wheel{ new GameObject{car} };
            new Renderer{ wheel, "../assets/wheel.png" };
            Rotor* rotor{ new Rotor{ wheel } };
            wheel->transform->position = sf::Vector2f{ 700, -700 };
            new WheelCarInput{ car, rotor, mover };

        }
    }
    return res;
}

void create_defualt_scene(GameObject*& scene,
    Camera*& camera,
    ServerIO& sio,
    int cnt, int ind) {
    scene = new GameObject{ nullptr };
    GameObject* map_drawer_go{ new GameObject{scene} };
    MapDrawer* map_drawer1{ new MapDrawer{
        map_drawer_go, "../configs/map1.json", false, sf::LinesStrip} };
    MapDrawer* map_drawer2{ new MapDrawer{
         map_drawer_go, "../configs/map2.json", false, sf::LinesStrip } };

    GameObject* check_origin{ new GameObject{scene} };
    RoadCheck* check{ new RoadCheck{
        check_origin,
        map_drawer1->coords.points,
        map_drawer2->coords.points
        }
    };

    std::vector<GameObject*> cars = create_cars(scene, cnt, camera, check, ind);
    Client* client = new Client{ cars[ind], sio, ind, cars };

    MapDrawer* map_drawer3{ new MapDrawer{
        map_drawer_go, "../configs/map3.json", false, sf::Lines
    } };

    GameObject* checkpoints_go{ new GameObject{scene} };
    LoopCounter* checkpoints{ new LoopCounter{checkpoints_go,
     map_drawer3->coords.points,
      cars[ind]->transform, 50, true} };
}

#endif
