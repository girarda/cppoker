#ifndef TELNETPLAYER_H_
#define TELNETPLAYER_H_

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include "network/OnlineRoom.h"
#include "network/OnlineUser.h"
#include "pokerGame/Hand.h"
#include "pokerGame/IPlayer.h"

namespace network
{

using boost::asio::ip::tcp;

enum SOCKET_READ_STATE {
    RS_WAITING_FOR_NAME,
    RS_WAITING_FOR_PLAY,
    RS_WAITING_FOR_CALL_BET,
    RS_NOT_WAITING
};

class TelnetPlayer : public pokerGame::IPlayer, public OnlineUser {

public:
    TelnetPlayer(boost::asio::io_service& io_service, OnlineRoom* room);
    ~TelnetPlayer();

    virtual void start();
    //void ReadyForInput();
    virtual tcp::socket& getSocket();

    bool isPlaying() const;

    virtual void seeDealer(std::string dealer);
    virtual void seeBigBlind(std::string player, float bigBlind);
    virtual void seeSmallBlind(std::string player, float smallBlind );
    virtual void seeRoundWinner(std::string winner);
    virtual void seeWinner(std::string winner);
    virtual void seeOpponentCards(std::string opponent, const pokerGame::Hand& hand);
    virtual void seeOpponentMoney(std::string opponent, float money);
    virtual void seeCards(const pokerGame::Hand& hand);
    virtual void seeMoney(float money);

    void sendChatMessage(std::string sender, std::string message);
    void seeCardDealt(const pokerGame::Hand& hand, const pokerGame::Card& new_card);
    pokerGame::Decision makeDecision(float minimumBid);

    virtual void deliver(const std::string& message);

private:
    tcp::socket socket;
    boost::asio::streambuf buffer;
    SOCKET_READ_STATE read_state;

    std::string choice;
    pokerGame::Decision decision;

    OnlineRoom* room;

    void handleRead(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);

    static const std::string TELNET_NEWLINE;

};

}

#endif
