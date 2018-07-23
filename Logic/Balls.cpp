//
// Created by kakise on 7/19/18.
//

#include "Balls.h"

bool Balls::isEnemy() const {
    return enemy;
}

int Balls::getDmg() const {
    return dmg;
}

void Balls::setDmg(int dmg) {
    Balls::dmg = dmg;
}

bool Balls::isBonus() const {
    return bonus;
}

int Balls::getBonusType() const {
    return bonusType;
}

float Balls::getBonusValue() const {
    return bonusValue;
}

int Balls::getGuide() const {
    return guide;
}

void Balls::setGuide(double guide) {
    Balls::guide = guide;
}

int Balls::getDirx() const {
    return dirx;
}
