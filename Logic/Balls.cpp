//
// Created by kakise on 7/19/18.
//

#include <iostream>
#include <random>
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

Balls::Balls(double guide, const sf::CircleShape &shape, int x, int y) : guide(std::fmod(guide, 2 * M_PI)),
                                                                         shape(shape) {
    Balls::getShape().setPosition(x, y);
    Balls::getShape().setFillColor(sf::Color::White);
}

sf::CircleShape &Balls::getShape() {
    return shape;
}

void Balls::moveBall() {
    sf::Time elapsed = Balls::cl.restart();

    // Tbh, it's simple trig
    Balls::getShape().setPosition(Balls::getShape().getPosition() +
                                  sf::Vector2f((float) cos(Balls::getGuide()), (float) -sin(Balls::getGuide())) *
                                  Balls::speed *
                                  elapsed.asSeconds());
}

void Balls::setSpeed(float ns) {
    Balls::speed = ns;
}

double Balls::getGuide() const {
    return guide;
}

void Balls::setGuide(double ng) {
    Balls::guide = std::fmod(ng, 2 * M_PI); // Add a security check.
}

void Balls::onCollision(int side) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 20 / 360 * 2 * M_PI);

    // In each case except the default one, I make a translation in the opposite direction of the collision.
    // It avoids the ball getting stuck outside the window for whatever reason.
    // Without these translation, bugs can happen and sometimes, the ball gets stuck outside the window.
    switch (side) {
        case 0:
            Balls::setGuide(2 * M_PI - (Balls::getGuide() + dist(rd)));
            Balls::getShape().setPosition(Balls::getShape().getPosition() - sf::Vector2f(0, 5));
            break;
        case 1:
            Balls::setGuide(M_PI - (Balls::getGuide() + dist(rd)));
            Balls::getShape().setPosition(Balls::getShape().getPosition() - sf::Vector2f(1, 0));
            break;
        case 2:
            Balls::setGuide(2 * M_PI - (Balls::getGuide() + dist(rd)));
            Balls::getShape().setPosition(Balls::getShape().getPosition() + sf::Vector2f(0, 1));
            break;
        case 3:
            Balls::setGuide(M_PI - (Balls::getGuide() + dist(rd)));
            Balls::getShape().setPosition(Balls::getShape().getPosition() + sf::Vector2f(1, 0));
            break;
        default:
            Balls::getShape().setPosition(0, 0);
            Balls::setGuide(M_PI / 4);
            break;
    }

}
