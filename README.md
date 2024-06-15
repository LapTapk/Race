# Race
## Руководство пользователя

Игра представляет собой гонки. Реализована только для Linux.

Перед запуском игры должен быть запущен сервер, чтобы его запустить, нужно запустить исполняемый файл build/server и передать ему аргумент в виде порта, на котором он будет слушать.
Чтобы запустить игру, необходимо запустить исполняемый файл, расположенный в build/main.
После запуска игры нужно ввести IP-адресс и порт, на которых запущен сервер.
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
