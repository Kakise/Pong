//
// Created by kakise on 7/19/18.
//

#ifndef PONG_BALLS_H
#define PONG_BALLS_H

#include <cmath>
#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES

/// Class containing logic to manage the ball and the consumable (they will be considered as balls for simplification's sake)
class Balls {
private:
    bool enemy = false;
    bool bonus = false;
    int dmg;

    int bonusType;
    float bonusValue;

    double guide = M_PI;
    float speed = 400;

    sf::CircleShape shape;

public:
    bool isBonus() const;
    int getDmg() const;
    void setDmg(int dmg);
    bool isEnemy() const;
    int getBonusType() const;
    float getBonusValue() const;

    sf::CircleShape &getShape();

    Balls(double guide, const sf::CircleShape &shape, int x, int y);

    void moveBall();

    void setSpeed(float ns);

    double getGuide() const;

    void setGuide(double ng);
};


#endif //PONG_BALLS_H
