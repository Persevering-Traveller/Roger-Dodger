#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game()
{
    windowWidth = 640;
    windowHeight = 480;
    windowName = "Roger Dodger";
    isRunning = true;
    game_state = GAME_STATE::PLAYING; // TODO: debugging change to START later

    fpsLimit = 60;

    pauseScreen.setSize(sf::Vector2f(640, 480));
    pauseScreen.setFillColor(sf::Color(200, 200, 200, 128));
}

Game::~Game()
{
    delete window;
    delete player;
}

void Game::init()
{
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName);
    window->setFramerateLimit(fpsLimit);

    player = new Player();
    player->init("./assets/Player.png");

    enemyHandler = new EnemyHandler();
    enemyHandler->init("./assets/Enemy.png");
}

void Game::run()
{
    while(isRunning)
    {
        update();
        draw();
    }

    quit();
    window->close();
}

void Game::update()
{
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            isRunning = false;
        }
        // Pause and Resume controls
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                if(game_state == GAME_STATE::PLAYING)
                    game_state = GAME_STATE::PAUSE;
                else if(game_state == GAME_STATE::PAUSE)
                    game_state = GAME_STATE::PLAYING;
                else if(game_state == GAME_STATE::START)
                    isRunning = false; // Close window if they hit escape at the start
            }
        }
    }

    if(game_state == GAME_STATE::PLAYING)
    {
        player->update();
        if(player->getHealth() <= 0)
            game_state = GAME_STATE::GAME_OVER; // change to game over screen
        
        enemyHandler->updatePool();
    }
}

void Game::draw()
{
    window->clear();
    switch(game_state)
    {
        case GAME_STATE::START:
            drawStartScreen();
            break;
        case GAME_STATE::PAUSE:
            // The pause screen still displays the play screen, just greys it out
            drawPlayScreen();
            drawPauseScreen();
            break;
        case GAME_STATE::PLAYING:
            drawPlayScreen();
            break;
        case GAME_STATE::GAME_OVER:
            drawGameOverScreen();
            break;
    }
    window->display();
}

void Game::quit()
{
    // Nothing to really do right now. Deconstructor handles most of it.
}

void Game::drawPlayScreen()
{
    for(int i = 0; i < enemyHandler->getPoolSize(); i++)
    {
        window->draw(enemyHandler->getEnemy(i)->getSprite());
    }
    window->draw(player->getSprite());
}

// Draw a grey translucent rectangle over screen
// draw the text PAUSED
void Game::drawPauseScreen()
{
    //window->draw(pauseText);
    window->draw(pauseScreen);
}

// Show title screen
void Game::drawStartScreen()
{
    
}

// Draw the text GAME OVER
// Draw the text replay? Press enter
void Game::drawGameOverScreen()
{
    
}