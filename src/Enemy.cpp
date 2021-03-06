#include "Enemy.h"

Enemy::Enemy()
{
    awake = false;
    reset(); // You can't reset something new, but it makes sense :)
    timer = std::rand() % RESPAWN_TIME;
}

void Enemy::init(sf::Texture &tex)
{
    sprite.setTexture(tex);
}

void Enemy::update()
{
    // Update the edge's location with its sprite
    edge = sf::Rect<float>(sprite.getGlobalBounds().left - 5,
                            sprite.getGlobalBounds().top,
                            sprite.getGlobalBounds().width + 10,
                            sprite.getGlobalBounds().height
                            );

    // Make awake if the countdown timer finally  hits respawn time
    if(!awake && timer > RESPAWN_TIME)
        awake = true;

    // Fall to the bottom of the screen
    if(awake)
        sprite.move(0, moveSpeed);
    else
        timer++;
    // Unload if past bottom
    if(sprite.getPosition().y > 480)
    {
        awake = false;
        reset();
    }
}

void Enemy::reset()
{
    // Random X position and top of screen
    position = sf::Vector2f(std::rand() % 608, -32);
    sprite.setPosition(position);
    moveSpeed = (std::rand() % 10) + 1; // Random speed from 1 to 10
    timer = 0;
    edge = sf::Rect<float>(sprite.getGlobalBounds().left - 5,
                            sprite.getGlobalBounds().top,
                            sprite.getGlobalBounds().width + 10,
                            sprite.getGlobalBounds().height
                            );
    touchedEdge = false;
}

sf::Rect<float> Enemy::getEdge()
{
    return edge;
}

void Enemy::setTouchedEdge(bool touched)
{
    touchedEdge = touched;
}

bool Enemy::getTouchedEdge()
{
    return touchedEdge;
}