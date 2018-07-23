#include <iostream>
#include <SFML/Graphics.hpp>
#include "Logic/Balls.h"

int main() {
    std::ios::sync_with_stdio(false);

    sf::RenderWindow window(sf::VideoMode(600, 400), "Pong NG+");
    sf::Clock clock;

    Balls menuBall(M_PI / 4, sf::CircleShape(5.f), 0, 0);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        menuBall.moveBall();

        window.clear();
        window.draw(menuBall.getShape());
        window.display();
    }

    return 0;
}