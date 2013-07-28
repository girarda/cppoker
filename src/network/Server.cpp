#include <boost/bind.hpp>

#include "network/Server.h"
#include "network/TelnetPlayer.h"

namespace network
{

Server::Server(OnlineRoom* onlineRoom) :
    ioService(),
    room(onlineRoom),
    connectionAcceptor(ioService, tcp::endpoint(tcp::v4(), TELNET_PORT_NUMBER)),
    threads()
{
}

Server::~Server()
{
    ioService.stop();
    threads.join_all();
}

void Server::initService()
{
    startAccept();
    for (int i = 0; i < 2; i++)
    {
        threads.create_thread(
                    [&]()
        {
            ioService.run();
        });
    }
    ioService.run();
}

void Server::startAccept() {

    TelnetPlayer *newPlayer = new TelnetPlayer(ioService, room);

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
