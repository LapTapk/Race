# Race
## Руководство пользователя

Игра представляет собой гонки. Реализована только для Linux. Суть игры заключается в том, чтобы набрать как можно больше очков.
Для того, чтобы начать разгоняться необходимо нажать и держать нажатой клавишу W. Управление осуществлятся поворотом руля, который контролируется мышью.
На бездорожье добавляется вектор ускорения, который противодействует движению, постепенно он снизит скорость до 0, если отстутсвует газ. При езде по дороге вектор ускорения не модифируется.
### Запуск игры и сервера
Для запуска игры, необходимо предварительно запустить сервер
Запуск сервера проивзодится в следующем формате:
./server [port]
Для запуска сервера необходимо перейти в папку ./build и выполнить оттуда запуск файла server.
Запуск игры проивзодится выполнением файла ./main, передавать дополнительные аргументы НЕ нужно.
Далее программа попросит последовательно ввести сначала IP адрес сервера, а потом - порт, который слушает сервер.
Если сервер запущен локально - можно использовать 127.0.0.1 в качестве IP адреса и порт, который вы указали при запуске.
Далее программа предложит отправить любой символ, чтобы подтвердить готовность. Сразу после подключения этого делать не стоит, необходимо дождаться пока все игроки инициализируют программу. После чего каждый должен подтвердить готовность.
Как только все игроки будут готовы, запустится сама игра.
## Руковдоство разработчика
### Установка зависимостей
Зависимости проекта Race:
* SFML 2.5
```apt install libsfml-dev```
* jsoncpp 1.9.5
```apt install libjsoncpp-dev```
* boost 1.84
```apt install libboost-dev```
### Архитектура Race
Проект Race построен на самописной игровой архитектуре. Этот движок позвояляет с относительной простотой определять логику игры. 
Основным классом проекта является Game. Основным классом игрового пространства является GameObject. Игровое пространство представялет собой дерево, узлами которого являются GameObject, они связаны отношениями родитель-ребенок. Узел без родителя называется сценой. 
Поведение объекта в каждом кадре определяется списком его компонентов.

Приведем пример простой игры

Файл main.cpp будет выглядеть следующим образом:
```
#include "game.hpp"
#include "game_object.hpp"
#include "game_conf.hpp"
#include "components.hpp"
#include <SFML/Graphics.hpp>

void create_scene(GameObject*& scene, Camera*& camera) {
    scene = new GameObject{nullptr};
    camera = new Camera{scene};

    GameObject* go{scene};
    Renderer* renderer{new Renderer{go, "path/to/img"}};
    Movement* mover{new Movement{go}};
    mover->vector = sf::Vector2{1, 0};
}

int main() {

    GameObject* scene;
    Camera* camera;
    create_scene(scene, camera);

    GameConf conf{"path/to/conf"};
    Game game{conf, scene, camera};
    game.run();
}
```
