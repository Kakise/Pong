#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Logic/Balls.h"
#include "Levels/DifficultySelection.h"
#include "Levels/LoadLevel.h"

#ifdef __APPLE__
#define ASSETS_DIR "../Resources"
#elif
#define ASSETS_DIR "Assets"
#endif

int main() {
    std::ios::sync_with_stdio(false);
    // Useful vars
    int selector(0);
    int levelDiff;
    std::string level;

    // Music
    sf::Music menuMusic;
    if (!menuMusic.openFromFile(std::string(ASSETS_DIR) + "/menu.ogg"))
        std::cerr << "Error opening 'menu.ogg' music" << std::endl;
    menuMusic.play();
    menuMusic.setLoop(true);

    // Fonts and text
    sf::Font pixel;
    if (!pixel.loadFromFile(std::string(ASSETS_DIR) + "/pixel.ttf")) {
        std::cerr << "Error opening 'pixel.ttf' font" << std::endl;
        return EXIT_FAILURE; // I can't display text without any font so if it can't be loaded, just let's exit the program.
    }
    sf::Text title("Pong NG+", pixel, 24);
    title.setPosition(375, 250);
    sf::Text start("Start", pixel, 20);
    start.setPosition(400, 400);
    start.setFillColor(sf::Color::Red);
    sf::Text options("Options", pixel, 20);
    options.setPosition(388, 435);
    sf::Text exit("Exit", pixel, 20);
    exit.setPosition(409, 470);

    // Images and textures
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile(std::string(ASSETS_DIR) + "/menu.png", sf::Rect(0, 0, 800, 600)))
        std::cerr << "Can't load 'menu.png' texture" << std::endl;
    sf::Sprite menuSpr(menuTexture);

    // Window Creation
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(800, 600, 16), "Pong NG+", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setMouseCursorVisible(false);

    // Shader
    sf::Shader shader;
    if (!sf::Shader::isAvailable())
        std::cerr << "Can't use shader" << std::endl;
    if (!shader.loadFromFile(std::string(ASSETS_DIR) + "/scanline.frag", sf::Shader::Fragment))
        std::cerr << "Can't load 'scanline.frag' shader" << std::endl;

    // Ball spawning
    Balls menuBall(M_PI / 5, sf::CircleShape(5.f), window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen()) {

        // Catch the events
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Up)
                        selector = (selector - 1) % 3;
                    if (event.key.code == sf::Keyboard::Down)
                        selector = (selector + 1) % 3;
                    switch (selector) {
                        case 0:
                            start.setFillColor(sf::Color::Red);
                            options.setFillColor(sf::Color::White);
                            exit.setFillColor(sf::Color::White);
                            break;
                        case 1:
                            start.setFillColor(sf::Color::White);
                            options.setFillColor(sf::Color::Red);
                            exit.setFillColor(sf::Color::White);
                            break;
                        case 2:
                            start.setFillColor(sf::Color::White);
                            options.setFillColor(sf::Color::White);
                            exit.setFillColor(sf::Color::Red);
                            break;
                        default:
                            break;
                    }
                    if (event.key.code == sf::Keyboard::Return)
                        switch (selector) {
                            case 0:
                                levelDiff = DifficultySelection(&window, menuBall, &level);
                                LoadLevel(level, &window, &menuMusic, levelDiff);
                                break;
                            case 1:
                                window.clear();
                                break;
                            case 2:
                                window.close();
                                break;
                            default:
                                break;
                        }
                    break;
                default:
                    break;
            }
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

        // Update the window content
        window.clear();
        window.draw(menuSpr);
        window.draw(menuBall.getShape());
        window.draw(title);
        window.draw(start);
        window.draw(options);
        window.draw(exit);
        window.display();
    }

    return 0;
}