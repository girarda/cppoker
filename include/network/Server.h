#ifndef TELNETSERVER_H_
#define TELNETSERVER_H_

#include <boost/asio.hpp>
#include "network/OnlineRoom.h"
#include "network/OnlineUser.h"
#include "pokerGame/IPlayer.h"

namespace network
{

using boost::asio::ip::tcp;

const short TELNET_PORT_NUMBER = 13305;

class Server {
public:
    Server(OnlineRoom* onlineRoom);
    void initService();
private:
    boost::asio::io_service ioServer;
    tcp::acceptor connectionAcceptor;

    OnlineRoom* room;

    void startAccept();
    void handleAccept(OnlineUser* newUser, const boost::system::error_code& error);
};

}

#endif
