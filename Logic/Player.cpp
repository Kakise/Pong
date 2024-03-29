#include <utility>

#include <utility>

//
// Created by kakise on 7/19/18.
//

#include <iostream>
#include "Player.h"

void Player::move(float relative_up) {
    float deltaTime = Player::clock.restart().asSeconds();
    Player::playerSpr.move(0, -relative_up * m_speed * deltaTime);
}

/// This functions has to be called when the player collides with another object (ie a ball). It handles bonuses, bouncing of a ball, etc...
/// \param ball The ball that collided with the player.
/// \param side The side of the ball that collided (0 = up, 1 = right, 2 = bottom, 3 = left).
void Player::onCollision(Balls &ball, int side) {

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

Player::Player(int lives, float m_speed, sf::Sprite playerSpr, sf::Vector2f position) : lives(lives), m_speed(m_speed),
                                                                                        playerSpr(
                                                                                                std::move(playerSpr)) {
    sf::Clock clock;
    if (!Player::tex.loadFromFile(std::string(ASSETS_DIR) + "/paddle.png")) {
        std::cerr << "Can't load 'paddle.png' image, exiting..." << std::endl;
    }
    Player::playerSpr = sf::Sprite(tex);
    Player::playerSpr.setPosition(position);
}

Player::Player(int lives, float m_speed, sf::Sprite playerSpr, float x, float y) : lives(lives), m_speed(m_speed),
                                                                                   playerSpr(std::move(playerSpr)) {
    sf::Clock clock;
    if (!Player::tex.loadFromFile(std::string(ASSETS_DIR) + "/paddle.png")) {
        std::cerr << "Can't load 'paddle.png' image, exiting..." << std::endl;
    }
    Player::playerSpr = sf::Sprite(tex);
    Player::playerSpr.setPosition(x, y);

}

sf::Sprite Player::getSprite() const {
    return Player::playerSpr;
}
