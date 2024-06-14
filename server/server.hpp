#ifndef SERVER_HPP
#define SERVER_HPP
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

using boost::asio::ip::tcp;

std::mutex clients_mutex; ///> синхронизация подключенных клиентов для защиты общих данных от единовременного доступа несколькими потоками
/**
 * Структора, определяющая подключение и его номер
 * Позволяет знать номер каждого игрока, в соответствии с его подключением
*/
struct player
{
    int number_; ///> Номер игрока
    std::shared_ptr<tcp::socket> socket_; ///> Сокет игрока
    bool is_ready_; ///> Переменная определяющая готовность игрока
    /**
     * Конструктор структоры игрока
     * 
     * @param socket Передаваемый указатель на сокет подключения
     * @param number Порядковый номер подключения
    */
    player(std::shared_ptr<tcp::socket> socket, int number);
};

std::vector<player> players; ///> Вектор подключенных игроков
/**
 * Функция, позволяющая найти игрока по его подключению
 * @param s Сокет игрока, который необходимо найти среди других подключений
*/
std::vector<player>::iterator find_player_by_socket(
    std::shared_ptr<tcp::socket> &s);
/**
 * Функция, осуществляющая перехват данных, полученных от пользователей
 * @param socket Передаваемый указатель на сокет пользователя, от которого было получено сообщение
*/
void handle_client(std::shared_ptr<tcp::socket> socket);

#endif