#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

class Enemy : public Entity
{
    public:
        Enemy();
        void init(sf::Texture &tex);
        void update();
        void reset();

    private:
        static const int RESPAWN_TIME = 120;
        int timer;
        bool awake;
};

#endif