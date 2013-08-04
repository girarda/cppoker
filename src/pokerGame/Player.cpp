#include "pokerGame/Player.h"

namespace pokerGame
{
    Player::Player() : name("Anon")
    {
    }

    Player::~Player()
    {
    }


    std::string Player::getName() const
    {
        return name;
    }

    void Player::setName(std::string newName)
    {
        name = newName;
    }
}
