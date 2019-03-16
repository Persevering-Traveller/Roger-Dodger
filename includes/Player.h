#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player : public Entity
{
    public:
        Player();
        virtual ~Player();
        int getHealth();
        void init(std::string fileLoc);
        void update();
        void draw(); //TODO: Consider deleting

    private:
        int health;

        void controls();
        void damage();
};

#endif // PLAYER_H
