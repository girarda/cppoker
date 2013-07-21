#ifndef TELNETPLAYER_H_
#define TELNETPLAYER_H_

#include <boost/asio.hpp>
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
    RS_NOT_WAITING
};

class TelnetPlayer : public pokerGame::IPlayer, public OnlineUser {

public:
    TelnetPlayer(boost::asio::io_service& io_service, OnlineRoom* room);
    virtual void start();
    //void ReadyForInput();
    virtual tcp::socket& getSocket();

    bool isPlaying();
    std::string getName();
    float getTotalBalance();
    void setTotalBalance(float new_value);

    virtual void seeDealer(std::string dealer) const;
    virtual void seeBigBlind(std::string player, float bigBlind) const;
    virtual void seeSmallBlind(std::string player, float smallBlind ) const;
    virtual void seeWinner(std::string winner) const;
    virtual void seeOpponentCards(std::string opponent, const pokerGame::Hand& hand) const;
    virtual void seeOpponentMoney(std::string opponent, float money) const;
    virtual void seeCards(const pokerGame::Hand& hand) const;
    virtual void seeMoney(float money) const;

    void sendChatMessage(std::string sender, std::string message);
    void seeCardDealt(const pokerGame::Hand& hand, const pokerGame::Card& new_card);
    pokerGame::Decision makeDecision(float minimum_bid);

    virtual void deliver(const std::string& msg);

private:
    tcp::socket socket;
    boost::asio::streambuf buffer;
    SOCKET_READ_STATE read_state;

    std::string name;
    float total_balance;

    OnlineRoom* room;

    void setName(const std::string& name);

    void write(const std::string& message);
    void handleRead(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);

    ~TelnetPlayer();
};

}

#endif
