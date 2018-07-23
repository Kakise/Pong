//
// Created by kakise on 7/19/18.
//

#include "Balls.h"

sf::Clock cl;

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

Balls::Balls(double guide, const sf::CircleShape &shape, int x, int y) : guide(guide), shape(shape) {
    getShape().setPosition(x, y);
    getShape().setFillColor(sf::Color::White);
}

sf::CircleShape &Balls::getShape() {
    return shape;
}

void Balls::moveBall() {
    sf::Time elapsed = cl.restart();

    // Tbh, it's simple trig
    Balls::shape.setPosition(Balls::shape.getPosition() +
                             sf::Vector2f((float) cos(Balls::guide), (float) sin(Balls::guide)) * Balls::speed *
                             elapsed.asSeconds());
}

void Balls::setSpeed(float ns) {
    Balls::speed = ns;
}

double Balls::getGuide() const {
    return guide;
}

void Balls::setGuide(double ng) {
    Balls::guide = ng;
}