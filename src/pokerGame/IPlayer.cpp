#include "pokerGame/IPlayer.h"

namespace pokerGame
{
    IPlayer::IPlayer() : name("Anon")
    {
    }

    IPlayer::~IPlayer()
    {
    }


    std::string IPlayer::getName() const
    {
        return name;
    }

    void IPlayer::setName(std::string newName)
    {
        name = newName;
    }
}
