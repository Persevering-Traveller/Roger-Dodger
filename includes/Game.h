#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "EnemyHandler.h"

enum class GAME_STATE { START, PLAYING, PAUSE, GAME_OVER };

class Game
{
    public:
        Game();
        sf::RenderWindow window;

        void init();
        void run();

    private:
        int windowWidth, windowHeight;
        std::string windowName;
        bool isRunning;
        GAME_STATE gameState;

        int fpsLimit;
        int score;
        int timer;
        int scoreTickUp;
        std::string gameoverString;

        void update();
        void draw();
        void reset();

        // Screen Drawing Routines
        void drawPlayScreen();
        void drawPauseScreen();
        void drawStartScreen();
        void drawGameOverScreen();

        Player player;
        EnemyHandler enemyHandler;

        sf::RectangleShape pauseScreen;
        sf::Font font;
        sf::Text hud;
        sf::Text scoreText;
        sf::Text startText;
        sf::Text pauseText;
        sf::Text gameoverText;

        sf::SoundBuffer buffer;
        sf::Sound hurtSound;
        sf::Music gameplayMusic;

        
};

#endif // GAME_H
