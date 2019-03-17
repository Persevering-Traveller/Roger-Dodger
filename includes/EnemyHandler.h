#ifndef ENEMY_HANDLER_H
#define ENEMY_HANDLER_H
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EnemyHandler
{
    public:
        EnemyHandler();
        ~EnemyHandler();
        void init(std::string fileLoc);
        void updatePool();
        void drawPool();
        int getPoolSize();
        Enemy* getEnemy(int which);
        void resetPool();

    private:
        // List that will hold the enemyPool at a MAX_POOL_SIZE
        sf::Texture sharedTexture;
        static const int MAX_POOL_SIZE = 40;
        Enemy enemyPool[MAX_POOL_SIZE];
};

#endif