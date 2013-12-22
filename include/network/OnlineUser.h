#ifndef ONLINEUSER_H
#define ONLINEUSER_H

#include "boost/asio.hpp"

namespace network {

using boost::asio::ip::tcp;

class OnlineUser {
public:
    virtual void start() = 0;
    virtual tcp::socket& getSocket() = 0;
};

}

#endif
