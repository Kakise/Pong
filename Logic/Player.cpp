//
// Created by kakise on 7/19/18.
//

#include <iostream>
#include "Player.h"

void Player::move(float relative_up) {

}

/// This functions has to be called when the player collides with another object (ie a ball). It handles bonuses, bouncing of a ball, etc...
/// \param ball The ball that collided with the player.
/// \param side The side of the ball that collided (0 = up, 1 = right, 2 = bottom, 3 = left).
void Player::onCollision(Balls ball, int side) {

    // Here I check the nature of the ball and determine what to do.
    if (ball.isEnemy()) {
        Player::setLives(Player::getLives() - ball.getDmg());

    } else if (ball.isBonus()) {
        switch (ball.getBonusType()) {
            case 1: {
                auto bonus = (int) std::trunc(ball.getBonusValue());
                Player::setLives(Player::getLives() + bonus);
                break;
            }
            default:
                break;
        }

    } else {
        ball.onCollision(side);

    }
}


int Player::getLives() const {
    return lives;
}

void Player::setLives(int lives) {
    Player::lives = lives;
}
