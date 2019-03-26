#include "EnemyHandler.h"

void EnemyHandler::init(std::string fileLoc)
{
    if(!sharedTexture.loadFromFile(fileLoc))
        printf("Error loading enemy shared texture\n");
    else
    {
        for(auto &enemy : enemyPool)
        {
            enemy.init(sharedTexture);
        }
    }
    
}

void EnemyHandler::updatePool()
{
    for(auto &enemy : enemyPool)
    {
        enemy.update();
    }
}

int EnemyHandler::getPoolSize()
{
    return MAX_POOL_SIZE;
}

Enemy* EnemyHandler::getEnemy(int which)
{
    return &enemyPool[which];
}

void EnemyHandler::resetPool()
{
    for(auto &enemy : enemyPool)
        enemy.reset();
}