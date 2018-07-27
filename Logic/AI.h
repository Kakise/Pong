//
// Created by kakise on 7/19/18.
//

#ifndef PONG_AI_H
#define PONG_AI_H


#include "Player.h"

class AI : public Player {
private:
    int m_difficulty;

public:
    void diffUpdate();

    void update(Balls &ball);

    AI(int lives, float m_speed, const sf::Sprite &spr, float x, float y, int m_difficulty);

};


#endif //PONG_AI_H
