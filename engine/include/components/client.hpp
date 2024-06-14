#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include "game_object.hpp"
#include "components/transform.hpp"
#include "server_io.hpp"

using boost::asio::ip::tcp;
/**
 * Класс, отвечающий за создание и отправку сообщений серверу
 * Обладает компонентами, определяющими его поведение
*/
class Client : public Component {
public:
    ServerIO& sio; ///> Обьект, позволяющий осуществлять подключение к серверу
    std::vector<sf::Vector2f> coords; ///> координаты игрока, которые будут переданы серверу
    std::vector<GameObject*> players; ///> Обьекты игроков, позиции которых должны быть изменены
    int this_ind; ///> Индекс главного игрока
    std::string create_mes(); ///> Функция, вызываемая для создания сообщения
    /**
     * Функция парсинга, полученных от сервера, координат
     * 
     * @param mes строковое сообщение, полученное от сервера, из которого необходимо получить координаты
    */
    void parse_coords(
        std::string mes);
    /**
     * Конструктор класса клиента
     * 
     * @param go Указатель на GameObject, который является родительским объектом
     * @param sio Параметр подключения к серверу, позволяющий осуществлять отправку и получение сообщений
     * @param this_ind Индекс главного игрока
     * @param players Вектор из обьектов других игроков, учавствующих в игре
    */
    Client(GameObject* go, ServerIO& sio,
        int this_ind, std::vector<GameObject*> players);
    void set_positions(); ///> функция, вызываемая для обновлений координат игроков
    void update() override; ///> функция обработки кадра
};

#endif