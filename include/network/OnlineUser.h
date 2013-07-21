#ifndef ONLINEUSER_H
#define ONLINEUSER_H

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class OnlineUser
{
public:
    virtual void start() = 0;
    virtual tcp::socket& GetSocket() = 0;

};

#endif // ONLINEUSER_H
