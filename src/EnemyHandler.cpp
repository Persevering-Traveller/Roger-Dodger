#include "EnemyHandler.h"

EnemyHandler::EnemyHandler()
{

}

EnemyHandler::~EnemyHandler()
{

}

void EnemyHandler::init(std::string fileLoc)
{
    if(!sharedTexture.loadFromFile(fileLoc))
        printf("Error loading enemy shared texture\n");
    else
    {
        for(int i = 0; i < MAX_POOL_SIZE; i++)
        {
            enemyPool[i].init(sharedTexture);
        }
    }
    
}

void EnemyHandler::updatePool()
{
    for(int i = 0; i < MAX_POOL_SIZE; i++)
    {
        enemyPool[i].update();
    }
}

void EnemyHandler::drawPool()
{
    // call each enemy's draw
}

int EnemyHandler::getPoolSize()
{
    return MAX_POOL_SIZE;
}

Enemy* EnemyHandler::getEnemy(int which)
{
    return &enemyPool[which];
}