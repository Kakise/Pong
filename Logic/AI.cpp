//
// Created by kakise on 7/19/18.
//

#include <iostream>
#include "AI.h"


void AI::diffUpdate() {


}

AI::AI(int lives, float m_speed, const sf::Sprite &spr, float x, float y, int m_difficulty) : Player(lives, m_speed,
                                                                                                     spr, x, y),
                                                                                              m_difficulty(
                                                                                                      m_difficulty) {
    sf::Clock clock;
    if (!Player::tex.loadFromFile(std::string(ASSETS_DIR) + "/paddle.png")) {
        std::cerr << "Can't load 'paddle.png' image, exiting..." << std::endl;
    }
    Player::playerSpr = sf::Sprite(tex);
    Player::playerSpr.setPosition(x, y);
    Player::playerSpr.setOrigin(Player::playerSpr.getLocalBounds().width / 2,
                                Player::playerSpr.getLocalBounds().height / 2);

}

void AI::update(Balls &ball) {
    if (ball.getShape().getPosition().x > 400) {
        if (ball.getShape().getPosition().y > playerSpr.getPosition().y &&
            playerSpr.getPosition().y < 600 - playerSpr.getOrigin().y)
            move(-1);
        if (ball.getShape().getPosition().y < playerSpr.getPosition().y &&
            playerSpr.getPosition().y > playerSpr.getOrigin().y)
            move(1);
    } else {
        move(0);
    }
}
