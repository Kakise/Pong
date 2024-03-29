//
// Created by kakise on 7/26/18.
//

#include "DifficultySelection.h"

namespace fs = std::filesystem;

int DifficultySelection(sf::RenderWindow *window, Balls menuBall, std::string *level) {
    int selector(0);
    int levelSelector(0);
    int selected(0);
    window->clear();

    std::vector<std::string> dir;
    for (auto const p : fs::directory_iterator(std::string(ASSETS_DIR) + "/Levels"))
        dir.push_back(p.path());

    // Fonts and text
    sf::Font pixel;
    if (!pixel.loadFromFile(std::string(ASSETS_DIR) + "/pixel.ttf")) {
        std::cerr << "Error opening 'pixel.ttf' font" << std::endl;
        exit(EXIT_FAILURE); // I can't display text without any font so if it can't be loaded, just let's exit the program.
    }
    sf::Text title("Pong NG+", pixel, 24);
    title.setPosition(375, 250);
    sf::Text levelSelect(dir[0], pixel, 20);
    levelSelect.setPosition(375, 220);
    sf::Text easy("Easy", pixel, 20);
    easy.setPosition(405, 400);
    easy.setFillColor(sf::Color::Red);
    sf::Text medium("Medium", pixel, 20);
    medium.setPosition(385, 435);
    sf::Text hard("Hard", pixel, 20);
    hard.setPosition(405, 470);

    // Images & Textures
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile(std::string(ASSETS_DIR) + "/menu.png", sf::Rect(0, 0, 800, 600)))
        std::cerr << "Can't load 'menu.png' texture" << std::endl;
    sf::Sprite menuSpr(menuTexture);

    while (!selected) {
        // Catch the events
        sf::Event event{};
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    exit(EXIT_SUCCESS);
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Right)
                        levelSelector = static_cast<int>((levelSelector + 1) % dir.size());
                    if (event.key.code == sf::Keyboard::Left)
                        levelSelector = static_cast<int>((levelSelector - 1) % dir.size());
                    if (event.key.code == sf::Keyboard::Up)
                        selector = (selector - 1) % 3;
                    if (event.key.code == sf::Keyboard::Down)
                        selector = (selector + 1) % 3;
                    switch (selector) {
                        case 0:
                            easy.setFillColor(sf::Color::Red);
                            medium.setFillColor(sf::Color::White);
                            hard.setFillColor(sf::Color::White);
                            break;
                        case 1:
                            easy.setFillColor(sf::Color::White);
                            medium.setFillColor(sf::Color::Red);
                            hard.setFillColor(sf::Color::White);
                            break;
                        case 2:
                            easy.setFillColor(sf::Color::White);
                            medium.setFillColor(sf::Color::White);
                            hard.setFillColor(sf::Color::Red);
                            break;
                        default:
                            break;
                    }
                    if (event.key.code == sf::Keyboard::Return)
                        selected = 1;
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


        *level = dir[levelSelector];
        char c = '/';
        levelSelect.setString(split(*level, c)[2]);
        levelSelect.setOrigin(levelSelect.getLocalBounds().width / 2, levelSelect.getLocalBounds().height / 2);
        levelSelect.setPosition(437.5, 300);

        window->clear();
        window->draw(menuSpr);
        window->draw(menuBall.getShape());
        window->draw(title);
        window->draw(levelSelect);
        window->draw(easy);
        window->draw(medium);
        window->draw(hard);
        window->display();

    }

    return selector;

}