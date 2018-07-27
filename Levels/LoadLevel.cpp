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
    vector<vector<string>> levelOptions;
    ifstream file(fileName.c_str());

    string line;
    while (getline(file, line)) {
        levelOptions.push_back(split(line, ';'));
    }

    int speed, lives;
    stringstream customDiff(levelOptions[0][3]);
    difficulty = 50 * difficulty;
    customDiff >> difficulty;

    stringstream clives(levelOptions[0][1]);
    clives >> lives;

    stringstream cspeed(levelOptions[0][2]);
    cspeed >> speed;

    while (lives) {

    }
}
