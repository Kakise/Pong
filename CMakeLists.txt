cmake_minimum_required(VERSION 3.10)
project(Pong)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pong main.cpp GUI.cpp GUI.h Logic/AI.cpp Logic/AI.h Logic/Player.cpp Logic/Player.h Logic/Balls.cpp Logic/Balls.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Pong ${SFML_LIBRARIES})
endif ()