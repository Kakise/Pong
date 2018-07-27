//
// Created by kakise on 7/26/18.
//

#ifndef PONG_LOADLEVEL_H
#define PONG_LOADLEVEL_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Logic/Player.h"
#include "../Logic/AI.h"
#include "../Logic/Balls.h"

template<class T>
std::vector<T> split(T const &string, char c) {
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

    return vector;
}

void LoadLevel(std::string fileName, sf::RenderWindow *window, int difficulty);

#endif //PONG_LOADLEVEL_H