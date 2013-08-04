#ifndef ONLINEROOM_H
#define ONLINEROOM_H

#include "pokerGame/Player.h"
#include <string>

namespace network
{

class OnlineRoom
{
public:
    virtual ~OnlineRoom() {}
    virtual void join(pokerGame::Player* player) = 0;
    virtual void leave(pokerGame::Player* player) = 0;
    virtual void sendChatMessage(const std::string& mesage) = 0;
};

}

#endif
