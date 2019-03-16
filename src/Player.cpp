#include "Player.h"

Player::Player()
{
    health = 3;
    moveSpeed = 2.0f;
    position = sf::Vector2f(320, 400);
}

Player::~Player()
{
    //dtor
}

void Player::init(std::string fileLoc)
{
    setSprite(fileLoc);
    sprite.setPosition(position);
}

void Player::update()
{
    // Controls and reactions
    controls();
    // Damage control
    damage();
}

// TODO: Consider deleting since we have "getSprite"
void Player::draw()
{

}

int Player::getHealth()
{
    return health;
}

void Player::controls()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // Move left
        sprite.move(-moveSpeed, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // Move Right
        sprite.move(moveSpeed, 0);
    }
}

void Player::damage()
{
    // if player is hit by enemy
    // subtract one health
    // go invincible for 2 seconds
}