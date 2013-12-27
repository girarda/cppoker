#ifndef ONLINEROOM_H
#define ONLINEROOM_H

#include "pokerGame/PlayerController.h"
#include <string>

namespace network {

class OnlineRoom {
public:
    virtual ~OnlineRoom() {}
    virtual void join(pokerGame::PlayerController* player) = 0;
    virtual void leave(pokerGame::PlayerController* player) = 0;
    virtual void sendChatMessage(std::string mesage) = 0;
};

}

#endif
