//
// Created by kakise on 7/26/18.
//

#ifndef PONG_DIFFICULTYSELECTION_H
#define PONG_DIFFICULTYSELECTION_H

#ifdef __APPLE__
#define ASSETS_DIR "../Resources"
#elif
#define ASSETS_DIR "Assets"
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include "../Logic/Balls.h"

template<class T>
std::vector<T> split(T &string, char &c) {
    std::string buffer;
    std::vector<T> vector;

    for (auto n:string) {
        if (n != c) {
            buffer += n;
        } else {
            vector.push_back(buffer);
            buffer = "";
        }
    }
    vector.push_back(buffer);

    return vector;
}

int DifficultySelection(sf::RenderWindow *window, Balls menuBall, std::string *level);

#endif //PONG_DIFFICULTYSELECTION_H
