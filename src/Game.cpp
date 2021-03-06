#include "Game.h"
#include <SFML/Graphics.hpp>

Game::Game()
{
    windowWidth = 640;
    windowHeight = 480;
    windowName = "Roger Dodger";
    isRunning = true;
    gameState = GAME_STATE::START;

    fpsLimit = 60;
    score = 0;
    timer = 0;
    scoreTickUp = fpsLimit * 2; // Two seconds
    gameoverString = "GAME OVER\nENTER TO TRY AGAIN\nESCAPE TO CLOSE";
}

void Game::init()
{
    window.create(sf::VideoMode(windowWidth, windowHeight), windowName);
    window.setFramerateLimit(fpsLimit);

    player.init("./assets/Player.png");
    enemyHandler.init("./assets/Enemy.png");

    pauseScreen.setSize(sf::Vector2f(640, 480));
    pauseScreen.setFillColor(sf::Color(200, 200, 200, 128));

    if(!font.loadFromFile("./assets/Pixel12x10.ttf"))
        printf("Problem loading font!\n");
    else
    {
        hud.setFont(font);
        scoreText.setFont(font);
        startText.setFont(font);
        pauseText.setFont(font);
        gameoverText.setFont(font);

        hud.setString("Hits Left: " + std::to_string(player.getHealth()));
        scoreText.setString("SCORE: " + std::to_string(score));
        startText.setString("ROGER DODGER\nPRESS ENTER");
        pauseText.setString("PAUSE");
        gameoverText.setString(gameoverString);

        hud.setCharacterSize(16);
        scoreText.setCharacterSize(20);
        startText.setCharacterSize(24);
        pauseText.setCharacterSize(24);
        gameoverText.setCharacterSize(24);

        hud.setFillColor(sf::Color::Green);
        scoreText.setFillColor(sf::Color::White);
        startText.setFillColor(sf::Color::Green);
        pauseText.setFillColor(sf::Color::Green);
        gameoverText.setFillColor(sf::Color::White);

        hud.setPosition(20, 450);
        scoreText.setPosition(250, 30);
        startText.setPosition(220, 200);
        pauseText.setPosition(280, 200);
        gameoverText.setPosition(200, 160);
    }
;
    if(!gameplayMusic.openFromFile("./assets/neogauge.ogg"))
        printf("Problem loading music!\n");
    
    if(!buffer.loadFromFile("./assets/hurt.wav"))
        printf("Problem loading sound effect!\n");
    else
        hurtSound.setBuffer(buffer);
    
}

void Game::run()
{
    while(isRunning)
    {
        update();
        draw();
    }
    window.close();
}

void Game::update()
{
    sf::Event event;
    while(window.pollEvent(event))
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
                if(gameState == GAME_STATE::PLAYING)
                {
                    gameState = GAME_STATE::PAUSE;
                    gameplayMusic.pause();
                }
                else if(gameState == GAME_STATE::PAUSE)
                {
                    gameState = GAME_STATE::PLAYING;
                    gameplayMusic.play();
                }
                else if(gameState == GAME_STATE::START || gameState == GAME_STATE::GAME_OVER)
                    isRunning = false; // Close window if they hit escape at the start
            }

            // Start game from Start Screen
            if(event.key.code == sf::Keyboard::Return)
            {
                if(gameState == GAME_STATE::START)
                    gameState = GAME_STATE::PLAYING;
                else if (gameState == GAME_STATE::GAME_OVER)
                    reset();
            }
        }
    }

    if(gameState == GAME_STATE::PLAYING)
    {
        // This if guard is needed, otherwise it will attempt to start the music
        // ever frame and cause a segmentation fault!!
        if(gameplayMusic.getStatus() != sf::SoundSource::Status::Playing)
            gameplayMusic.play();
        
        // Collision testing
        for(int i = 0; i < enemyHandler.getPoolSize(); i++)
        {
            // Get actual enemy bounding box based on its sprite
            sf::Rect<float> enemyBounds(enemyHandler.getEnemy(i)->getSprite().getGlobalBounds());
            // If the player intersects its edge (a rect that also contains its bounding box)
            if(player.getSprite().getGlobalBounds().intersects(enemyHandler.getEnemy(i)->getEdge()))
            {
                // As long as the player is only intersecting with its edge, not its bounding box
                if(!player.getSprite().getGlobalBounds().intersects(enemyBounds))
                {
                    // If the enemy has not been touched by the player already
                    if(!enemyHandler.getEnemy(i)->getTouchedEdge())
                    {
                        // Add points and make it touched
                        score += 50;
                        enemyHandler.getEnemy(i)->setTouchedEdge(true);
                    }
                }
                else
                {
                    // Otherwise only hurt the player
                    player.hit();
                    // Another if guard to keep from playing the sound every single
                    // frame the player is hitting an enemy
                    if(player.getInvincibilityTimer() == 0)
                        hurtSound.play();
                }
            }  
        }
        
        player.update();
        hud.setString("Hits Left: " + std::to_string(player.getHealth()));
        scoreText.setString("SCORE: " + std::to_string(score));
        if(player.getHealth() <= 0)
        {
            gameState = GAME_STATE::GAME_OVER; // change to game over screen
            gameoverText.setString(gameoverString + "\n\nFINAL SCORE: " + std::to_string(score));
        }
        else
        {
            timer++;
            if(timer % scoreTickUp == 0)
                score += 10;
        }
        
        enemyHandler.updatePool();
    }
    else if(gameState == GAME_STATE::GAME_OVER)
    {
        // Another necessary if guard to not try to do this
        // every frame
        if(gameplayMusic.getStatus() != sf::SoundSource::Status::Stopped)
            gameplayMusic.stop();
    }
}

void Game::draw()
{
    window.clear();
    switch(gameState)
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
    window.display();
}

void Game::reset()
{
    player.reset();
    enemyHandler.resetPool();
    gameState = GAME_STATE::PLAYING;
    score = 0;
    timer = 0;
}

void Game::drawPlayScreen()
{
    for(int i = 0; i < enemyHandler.getPoolSize(); i++)
    {
        window.draw(enemyHandler.getEnemy(i)->getSprite());
    }
    window.draw(player.getSprite());
    window.draw(scoreText);
    window.draw(hud);
}

// Draw a grey translucent rectangle over screen
// draw the text PAUSED
void Game::drawPauseScreen()
{
    window.draw(pauseScreen);
    window.draw(pauseText);
}

// Show title screen
void Game::drawStartScreen()
{
    window.draw(startText);
}

// Draw game over text
void Game::drawGameOverScreen()
{
    window.draw(gameoverText);
}