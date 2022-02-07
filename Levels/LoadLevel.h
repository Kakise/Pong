//
// Created by kakise on 7/26/18.
//

#ifndef PONG_LOADLEVEL_H
#define PONG_LOADLEVEL_H

#ifdef __APPLE__
#define ASSETS_DIR "../Resources"
#elif
#define ASSETS_DIR "Assets"
#endif

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Logic/Player.h"
#include "../Logic/AI.h"
#include "../Logic/Balls.h"

void LoadLevel(std::string fileName, sf::RenderWindow *window, sf::Music *menuMusic, int difficulty);

#endif //PONG_LOADLEVEL_H