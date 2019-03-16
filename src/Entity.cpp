#include "Entity.h"

Entity::Entity()
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

sf::Sprite Entity::getSprite()
{
    return sprite;
}

void Entity::setSprite(std::string fileLocation)
{
    if(!texture.loadFromFile(fileLocation))
    {
        printf("Error loading %s\n", fileLocation.c_str());
    }
    else
    {
        sprite.setTexture(texture);
    }
}

// Virtual functions
void Entity::update(){}
void Entity::draw(){}
