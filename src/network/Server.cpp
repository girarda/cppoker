#include <boost/bind.hpp>

#include "network/Server.h"
#include "network/TelnetPlayer.h"

namespace network
{

Server::Server(OnlineRoom* onlineRoom) :
    ioServer(),
    room(onlineRoom),
    connectionAcceptor(ioServer, tcp::endpoint(tcp::v4(), TELNET_PORT_NUMBER))
{ }

void Server::initService() {

    startAccept();
    ioServer.run();

}

void Server::startAccept() {

    TelnetPlayer *newPlayer = new TelnetPlayer(ioServer, room);

    connectionAcceptor.async_accept(
                newPlayer->getSocket(),
                boost::bind(
                    &Server::handleAccept,
                    this,
                    newPlayer,
                    boost::asio::placeholders::error
                    )
                );

}

void Server::handleAccept(OnlineUser* newUser, const boost::system::error_code& error) {

    if (!error) {
        newUser->start();
    }

    startAccept();
}

}
