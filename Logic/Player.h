//
// Created by kakise on 7/19/18.
//

#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H


#include "Balls.h"
#include <SFML/Graphics.hpp>

class Player {
protected:
    int lives;
    sf::Texture tex;
    sf::Sprite playerSpr;
    sf::Clock clock;
    float m_speed;

public:
    void onCollision(Balls &ball, int side);

    Player(int lives, float m_speed, sf::Sprite spr, sf::Vector2f position);

    Player(int lives, float m_speed, sf::Sprite spr, float x, float y);

    void move(float relative_up);
    int getLives() const;
    void setLives(int lives);

    sf::Sprite getSprite() const;

};


#endif //PONG_PLAYER_H
