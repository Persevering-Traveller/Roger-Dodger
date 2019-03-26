#include "Entity.h"

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
