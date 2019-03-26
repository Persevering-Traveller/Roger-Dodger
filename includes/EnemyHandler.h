#ifndef ENEMY_HANDLER_H
#define ENEMY_HANDLER_H
#include <array>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EnemyHandler
{
    public:
        // Everything in a constructor is done better
        // in this init
        void init(std::string fileLoc);
        void updatePool();
        int getPoolSize();
        Enemy* getEnemy(int which);
        void resetPool();

    private:
        // List that will hold the enemyPool at a MAX_POOL_SIZE
        sf::Texture sharedTexture;
        static const int MAX_POOL_SIZE = 40;
        std::array<Enemy, MAX_POOL_SIZE> enemyPool;
};

#endif