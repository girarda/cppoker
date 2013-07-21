#ifndef ONLINEROOM_H
#define ONLINEROOM_H

#include "core/IPlayer.h"
#include <string>

namespace network
{

class OnlineRoom
{
public:
    virtual void join(pcore::IPlayer* player) = 0;
    virtual void leave(pcore::IPlayer* player) = 0;
    virtual void deliver(const std::string& mesage) = 0;
};

}

#endif
