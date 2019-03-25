#include "Player.h"

Player::Player()
{
    health = 3;
    timer = 0;
    invicibilityTime = 60; // 1 second
    hurt = false;
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

void Player::hit()
{
    hurt = true;
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

// subtract one health
// go invincible for 1 second
// make slightly transparent
void Player::damage()
{
    // if player is hit by enemy
    if(hurt)
    {
        // Can only count down health after timer resets
        if(timer == 0)
            health--;
        timer++;
        // Make slightly transparent while hurt and invincible
        sprite.setColor(sf::Color(255, 255, 255, 128));
    }
    if(timer >= invicibilityTime)
    {
        hurt = false;
        timer = 0;
        // Set back to original color
        sprite.setColor(sf::Color::White);
    }
   
}

// Set back to starting values
void Player::reset()
{
    health = 3;
    timer = 0;
    invicibilityTime = 60; // 1 second
    hurt = false;
    sprite.setPosition(position);
}