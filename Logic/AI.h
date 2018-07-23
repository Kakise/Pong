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

};


#endif //PONG_AI_H
