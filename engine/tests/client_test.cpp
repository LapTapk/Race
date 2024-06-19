#include "doctest.h"
#include "server_io.hpp"
#include "components/client.hpp"
#include <iostream>


ServerIO connection_1{"127.0.0.1", "12345"};
ServerIO connection_2{"127.0.0.1", "12345"};
ServerIO connection_3{"127.0.0.1", "12345"};
ServerIO connection_4{"127.0.0.1", "12345"};
ServerIO connection_5{"127.0.0.1", "12345"};
TEST_CASE("Send any data 100 times and reply same in other client"){
    std::string message{"anything"};
    for(int _{0}; _<100;_++){
    connection_1.send_message(message);
    while(connection_2.reply == ""){}
    CHECK_EQ(connection_2.reply, "1 " + message);
    connection_2.reply = "";
    }
    for(int _{0}; _<100;_++){
    connection_2.send_message(message);
    while(connection_1.reply == ""){}
    CHECK_EQ(connection_1.reply, "2 " + message);
    connection_1.reply = "";
    }
    
}
TEST_CASE("Send ready state and wait until other users sends it too"){
    connection_1.reply = "";
    connection_2.reply = "";
    connection_1.send_message("ready");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    connection_2.send_message("ready_");
    while(connection_1.reply == ""){
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    CHECK_EQ(connection_1.reply, "2 ready_");
    CHECK_EQ(connection_2.reply, "");
    connection_2.send_message("ready");
    connection_4.send_message("ready");
    connection_5.send_message("ready");
    connection_3.send_message("ready");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    CHECK_EQ(connection_1.reply, "5 1");
    CHECK_EQ(connection_2.reply, "5 2");
}

TEST_CASE("Send empty data"){
    connection_1.reply = "";
    connection_2.reply = "";
    connection_1.send_message("");
    connection_2.send_message("");
    CHECK_EQ(connection_1.reply, "");
    CHECK_EQ(connection_2.reply, "");
}

TEST_CASE("Multiply connection and ready state"){
    std::vector<ServerIO*> connections{&connection_1, &connection_2, &connection_3, &connection_4, &connection_5};
    for(int i{0}; i<=4; i++){
        connections[i]->send_message("ready");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for(int i{0}; i<=4; i++){
        CHECK_EQ(connections[i]->reply, "5 " + std::to_string(i+1));
    }
}
TEST_CASE("Multiply sending data"){
    std::vector<ServerIO*> connections{&connection_1, &connection_2, &connection_3, &connection_4, &connection_5};
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for(int i{0}; i<=4; i++){
        connections[i]->send_message("test");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        for(int j{0}; j<=4; j++){
            if (i == j){continue;}
            CHECK_EQ(connections[j]->reply,std::to_string(i+1) + " test" );
        }
    }
}

