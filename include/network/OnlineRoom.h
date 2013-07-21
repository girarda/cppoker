#ifndef ONLINEROOM_H
#define ONLINEROOM_H

#include "pokerGame/IPlayer.h"
#include <string>

namespace network
{

class OnlineRoom
{
public:
    virtual void join(pokerGame::IPlayer* player) = 0;
    virtual void leave(pokerGame::IPlayer* player) = 0;
    virtual void deliver(const std::string& mesage) = 0;
};

}

#endif
