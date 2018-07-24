#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Logic/Balls.h"

int main() {
    std::ios::sync_with_stdio(false);

    // Music
    sf::Music menuMusic;
    if (!menuMusic.openFromFile("Assets/menu.ogg"))
        std::cerr << "Error opening music file" << std::endl;
    menuMusic.play();
    menuMusic.setLoop(true);

    // Window Creation
    sf::RenderWindow window(sf::VideoMode(800, 600, 16), "Pong NG+", sf::Style::Titlebar + sf::Style::Close);
    window.setMouseCursorVisible(false);

    // Shader
    sf::Shader shader;
    if (!sf::Shader::isAvailable())
        std::cerr << "Can't use shader" << std::endl;
    if (!shader.loadFromFile("Assets/scanline.frag", sf::Shader::Fragment))
        std::cerr << "Can't load scanline shader" << std::endl;


    // Ball spawning
    Balls menuBall(M_PI / 5, sf::CircleShape(5.f), window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) {
        // Ensure the window will shutdown
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the menuBall
        menuBall.moveBall();

        // Detecting collision with the window. Window size independent.
        if (menuBall.getShape().getPosition().y < 0)
            menuBall.onCollision(2);
        else if (menuBall.getShape().getPosition().y > window.getSize().y)
            menuBall.onCollision(0);
        else if (menuBall.getShape().getPosition().x < 0)
            menuBall.onCollision(3);
        else if (menuBall.getShape().getPosition().x > window.getSize().x)
            menuBall.onCollision(1);

        // TODO: Main menu

        // Update the window content
        window.clear();
        window.draw(menuBall.getShape());
        window.display();
    }

    return 0;
}