#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

class Entity
{
    public:
        Entity();
        virtual ~Entity();
        virtual void update();
        virtual void draw(); //TODO: Consider deleting
        sf::Sprite getSprite();
        void setSprite(std::string fileLocation);

    protected:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f position;
        float moveSpeed;
};

#endif // ENTITY_H
