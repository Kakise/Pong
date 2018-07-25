//
// Created by kakise on 7/19/18.
//

#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H


#include "Balls.h"
#include <random>

class Player {
private:
    int lives;

protected:
    float m_speed;

public:
    void onCollision(Balls ball, int side);

    void move(float relative_up);
    int getLives() const;
    void setLives(int lives);

};


#endif //PONG_PLAYER_H
