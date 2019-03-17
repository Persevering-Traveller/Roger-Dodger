#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
    public:
        Player();
        virtual ~Player();
        int getHealth();
        void hit();
        void init(std::string fileLoc);
        void update();
        void draw(); //TODO: Consider deleting
        void reset();

    private:
        int health;
        int timer;
        int invicibilityTime;
        bool hurt;

        void controls();
        void damage();
};

#endif // PLAYER_H
