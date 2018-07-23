//
// Created by kakise on 7/19/18.
//

#include <iostream>
#include "Player.h"

void Player::move(float relative_up, float relative_right) {

}

// TODO: Add more bonuses
/// This functions has to be called when the player collides with another object (ie a ball). It handles bonuses, bouncing of a ball, etc...
/// \param ball The ball that collided with the player.
/// \param side The side of the ball that collided (0 = up, 1 = right, 2 = bottom, 3 = left).
void Player::onCollision(Balls ball, int side) {
    // Initialize the rng
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 5 / 360 * 2 * M_PI);

    // Here I check the nature of the ball and determine what to do.
    if (ball.isEnemy()) {
        setLives(getLives() - ball.getDmg());

    } else if (ball.isBonus()) {
        switch (ball.getBonusType()) {
            case 1: {
                auto bonus = (int) std::trunc(ball.getBonusValue());
                setLives(getLives() + bonus);
                break;
            }
            default:
                break;
        }

    } else {
        // Bouncing logic
        double newGuide;
        int diry = (ball.getGuide() >= 0 && ball.getGuide() <= M_PI) ? -1 : 1;
        switch (side) {
            case 1: // Right side (usually opponent)
                newGuide = ball.getGuide() - (M_PI / 2 + dist(rd)) * diry;
                break;
            case 3: // Left side (usually player)
                newGuide = ball.getGuide() + (M_PI / 2 + dist(rd)) * diry;
                break;
            default:
                newGuide = 0;
                std::cerr << "Error while computing a new direction." << std::endl;
                break;
        }
        ball.setGuide(newGuide);
    }

}

int Player::getLives() const {
    return lives;
}

void Player::setLives(int lives) {
    Player::lives = lives;
}
