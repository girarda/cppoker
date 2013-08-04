#ifndef TELNETSERVER_H_
#define TELNETSERVER_H_

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "network/OnlineRoom.h"
#include "network/OnlineUser.h"
#include "pokerGame/Player.h"

namespace network
{

using boost::asio::ip::tcp;

const short TELNET_PORT_NUMBER = 13305;

class Server {
public:
    Server(OnlineRoom* onlineRoom);
    ~Server();

    void initService();
private:
    void startAccept();
    void handleAccept(OnlineUser* newUser, const boost::system::error_code& error);

    boost::asio::io_service ioService;
    boost::asio::io_service::work work;
    tcp::acceptor connectionAcceptor;
    boost::thread_group threads;

    OnlineRoom* room;
};

}

#endif
