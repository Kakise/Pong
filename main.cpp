#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Logic/Balls.h"

int main() {
    std::ios::sync_with_stdio(false);

    // Music
    sf::Music menuMusic;
    if (!menuMusic.openFromFile("Assets/menu.ogg"))
        std::cerr << "Error opening 'menu.ogg' music" << std::endl;
    menuMusic.play();
    menuMusic.setLoop(true);

    // Images and textures
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("Assets/menu.png", sf::Rect(0, 0, 800, 600)))
        std::cerr << "Can't load 'menu.png' texture" << std::endl;
    sf::Sprite menuSpr(menuTexture);

    // Window Creation
    sf::RenderWindow window(sf::VideoMode(800, 600, 16), "Pong NG+", sf::Style::Titlebar | sf::Style::Close);
    window.setMouseCursorVisible(false);

    // Shader
    sf::Shader shader;
    if (!sf::Shader::isAvailable())
        std::cerr << "Can't use shader" << std::endl;
    if (!shader.loadFromFile("Assets/scanline.frag", sf::Shader::Fragment))
        std::cerr << "Can't load 'scanline.frag' shader" << std::endl;


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

        // Detecting collision with the window.
        if (menuBall.getShape().getPosition().y < 235)
            menuBall.onCollision(2);
        else if (menuBall.getShape().getPosition().y > 535)
            menuBall.onCollision(0);
        else if (menuBall.getShape().getPosition().x < 225)
            menuBall.onCollision(3);
        else if (menuBall.getShape().getPosition().x > 650)
            menuBall.onCollision(1);

        // TODO: Main menu

        // Update the window content
        window.clear();
        window.draw(menuSpr);
        window.draw(menuBall.getShape());
        window.display();
    }

    return 0;
}