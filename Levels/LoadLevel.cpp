//
// Created by kakise on 15/26/18.
//

#include "LoadLevel.h"

using namespace std;

/// This is used to fully loaded a level.
/// \param fileName Path of the level to load.
void LoadLevel(string fileName, sf::RenderWindow *window, int difficulty) {

    ///////////////////////////////////////////
    ///         STRUCTURE OF A LEVEL        ///
    ///////////////////////////////////////////
    ///      author lives speed aispeed     ///
    ///            bonus interval           ///
    ///////////////////////////////////////////
    ///  It is also possible to add custom  ///
    ///   walls by repeating the following  ///
    ///                line.                ///
    ///////////////////////////////////////////
    ///       pos_x pox_y height width      ///
    ///////////////////////////////////////////

    bool started(false);
    sf::Clock clock;
    sf::Time elapsed(clock.restart());

    // Load text and fonts
    sf::Font pixel;
    if (!pixel.loadFromFile("Assets/pixel.ttf")) {
        cerr << "Error opening 'pixel.ttf' font" << endl;
        exit(EXIT_FAILURE); // I can't display text without any font so if it can't be loaded, just let's exit the program.
    }
    sf::Text loading("Loading... (0/17)", pixel, 24);
    loading.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f));
    loading.setOrigin(loading.getLocalBounds().width / 2, loading.getLocalBounds().height / 2);
    window->clear();
    window->draw(loading);
    window->display();

    // Loading level
    vector<vector<int>> walls;
    ifstream file(fileName.c_str());

    string author;
    int lives, speed, aispeed, bonus, interval;

    file >> author;
    loading.setString("Loading... (1/17)");
    window->clear();
    window->draw(loading);
    window->display();

    file >> lives;
    loading.setString("Loading... (2/17)");
    window->clear();
    window->draw(loading);
    window->display();

    file >> speed;
    loading.setString("Loading... (3/17)");
    window->clear();
    window->draw(loading);
    window->display();

    file >> aispeed;
    aispeed += 50 * difficulty;
    loading.setString("Loading... (4/17)");
    window->clear();
    window->draw(loading);
    window->display();

    file >> bonus;
    loading.setString("Loading... (5/17)");
    window->clear();
    window->draw(loading);
    window->display();

    file >> interval;
    loading.setString("Loading... (6/17)");
    window->clear();
    window->draw(loading);
    window->display();

    string line;
    while (getline(file, line)) {
        stringstream tmp(line);
        int pos_x, pos_y, height, width;
        tmp >> pos_x;
        tmp >> pos_y;
        tmp >> height;
        tmp >> width,
                walls.push_back(vector<int>{pos_x, pos_y, height, width});
    }

    loading.setString("Loading... (7/17)");
    window->clear();
    window->draw(loading);
    window->display();

    // Images and textures
    sf::Texture court, paddle;
    if (!court.loadFromFile("Assets/court.png"))
        cerr << "Cannot load 'court.png' texture" << endl;
    if (!paddle.loadFromFile("Assets/paddle.png"))
        cerr << "Cannot load 'paddle.png' texture" << endl;
    sf::Sprite terrain(court), player(paddle);
    terrain.setPosition(0, 0);
    loading.setString("Loading... (11/17)");
    window->clear();
    window->draw(loading);
    window->display();

    // SFX
    sf::SoundBuffer bfrBump, bfrDeath;
    if (!bfrBump.loadFromFile("Assets/bump.ogg"))
        cerr << "Cannot load 'bump.ogg' sfx" << endl;
    if (!bfrDeath.loadFromFile("Assets/death.ogg"))
        cerr << "Cannot load 'death.ogg' sfx" << endl;
    sf::Sound bump(bfrBump), death(bfrDeath);
    loading.setString("Loading... (15/17)");
    window->clear();
    window->draw(loading);
    window->display();

    // Balls
    Balls ball(M_PI, sf::CircleShape(6.5f), window->getSize().x / 2, window->getSize().y / 2);
    ball.setSpeed(0);
    loading.setString("Loading... (16/17)");
    window->clear();
    window->draw(loading);
    window->display();

    // Player & AI
    Player player1(lives, 400, player, 0, (window->getSize().y - player.getLocalBounds().height) / 2);
    AI player2(lives, 400, player, window->getSize().x - player.getLocalBounds().width,
               (window->getSize().y - player.getLocalBounds().height) / 2, 50 * difficulty);
    loading.setString("Loading... (17/17)");
    window->clear();
    window->draw(loading);
    window->display();

    // Level loop
    while (window->isOpen()) {
        int direction(0);
        // Event catcher
        sf::Event event{};
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (!started) {
                        started = true;
                        ball.setSpeed(400 + 50 * difficulty);
                    }
                    break;
                default:
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player1.getSprite().getPosition().y > 0)
            direction = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            player1.getSprite().getPosition().y < (window->getSize().y - player1.getSprite().getLocalBounds().height))
            direction = -1;

        ball.moveBall();
        player1.move(direction);

        // Detecting collision with the window.
        if (ball.getShape().getPosition().y < 0)
            ball.onCollision(2);
        else if (ball.getShape().getPosition().y > window->getSize().y)
            ball.onCollision(0);

        // Detecting collision with the player and the AI
        if (player1.getSprite().getGlobalBounds().intersects(ball.getShape().getGlobalBounds()))
            player1.onCollision(ball, 3);
        if (player2.getSprite().getGlobalBounds().intersects(ball.getShape().getGlobalBounds()))
            player2.onCollision(ball, 1);

        player2.update(ball);
        // Detecting collision with the outer world

        window->clear();
        window->draw(terrain);
        window->draw(player1.getSprite());
        window->draw(player2.getSprite());
        window->draw(ball.getShape());
        window->display();
    }
}