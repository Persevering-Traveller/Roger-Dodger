#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

class Entity
{
    public:
        // No need for De/Constructors, everything
        // will be set up properly in its children
        virtual void update() = 0;
        sf::Sprite getSprite();
        void setSprite(std::string fileLocation);

    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f position;
        float moveSpeed;
};

#endif // ENTITY_H
