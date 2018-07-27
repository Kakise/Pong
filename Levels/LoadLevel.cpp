//
// Created by kakise on 7/26/18.
//

#include "LoadLevel.h"

using namespace std;

/// This is used to fully loaded a level.
/// \param fileName Path of the level to load.
void LoadLevel(string fileName, sf::RenderWindow *window, int difficulty) {

    ///////////////////////////////////////////
    ///         STRUCTURE OF A LEVEL        ///
    ///////////////////////////////////////////
    ///      author;lives;speed;aispeed     ///
    ///            bonus;interval           ///
    ///////////////////////////////////////////
    ///  It is also possible to add custom  ///
    ///   walls by repeating the following  ///
    ///                line.                ///
    ///////////////////////////////////////////
    ///       pos_x;pox_y;height;width      ///
    ///////////////////////////////////////////

    // 0 -> options. 1 -> bonus. 2+ -> walls
    vector<vector<int>> walls;
    fstream file(fileName.c_str());

    string author;
    int lives, speed, aispeed, bonus, interval;

    file >> author;
    file >> lives;
    file >> speed;
    file >> aispeed;
    file >> bonus;
    file >> interval;

    string line;
    while (getline(file, line)) {
        stringstream tmp(line);
        int pos_x, pos_y, height, width;
        tmp >> pos_x;
        tmp >> pos_y;
        tmp >> height;
        tmp >> width,
                walls.push_back(vector<int>{pos_x, pos_y, height, width});
    }


}
