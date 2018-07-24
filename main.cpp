#include <iostream>
#include <SFML/Graphics.hpp>
#include "Logic/Balls.h"

int main() {
    std::ios::sync_with_stdio(false);

    sf::RenderWindow window(sf::VideoMode(600, 400), "Pong NG+");
    sf::Clock clock;

    Balls menuBall(M_PI / 5, sf::CircleShape(5.f), window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        menuBall.moveBall();

        if (menuBall.getShape().getPosition().y < 0)
            menuBall.onCollision(2);
        else if (menuBall.getShape().getPosition().y > window.getSize().y)
            menuBall.onCollision(0);
        else if (menuBall.getShape().getPosition().x < 0)
            menuBall.onCollision(3);
        else if (menuBall.getShape().getPosition().x > window.getSize().x)
            menuBall.onCollision(1);

        window.clear();
        window.draw(menuBall.getShape());
        window.display();
    }

    return 0;
}