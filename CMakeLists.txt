cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_DEBUG_POSTFIX d)

project(Race)

link_libraries(sfml-window sfml-graphics sfml-system jsoncpp)

add_executable(main main.cpp)
target_include_directories(main PUBLIC scenes)

add_executable(server server/server.cpp)
target_include_directories(server PUBLIC server)

add_subdirectory(engine)