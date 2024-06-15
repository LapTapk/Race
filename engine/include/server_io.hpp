#ifndef SERVER_IO_HPP
#define SERVER_IO_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include "game_object.hpp"
#include "components/transform.hpp"

using boost::asio::ip::tcp;
/**
 * Класс, являющийся подключением к серверу
 * Определяет второй поток, отвечающий за асинхронное чтение из буфера сервера
*/
class ServerIO  {
public:
    std::string port; ///> Порт, по которому будет осуществлено подключение
    boost::asio::io_context io_context; ///> Объект испетчер асинхронных операций ввода-вывода
    tcp::socket socket; ///> Объект необходимый для двусторонней связи клиента и сервера
    std::string server_ip; ///> IP-адрес сервера, по которому будет осуществлено подключение
    std::thread* reader_thread; ///> указатель на поток чтения
    std::string reply{ "" }; ///> Переменная, которая хранит сообщения от сервера
    /**
     * Функция чтения сообщений от сервера
     * 
     * @param socket сокет подключения
    */
    void read_from_server(tcp::socket& socket);
    /**
     * Инициализатор ServerIO подключения
     * 
     * @param server_ip ip-адрес сервера
     * @param port порт, который слушает сервер
    */
    ServerIO(std::string server_ip, std::string port);
    /**
     * Функция отправки сообщения на сервер
     * 
     * @param mes сообщение, готовое к отправке серверу
    */
    void send_message(std::string mes);
    ~ServerIO(); ///> Деструктор
};

#endif