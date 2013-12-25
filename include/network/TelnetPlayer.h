#ifndef TELNETPLAYER_H_
#define TELNETPLAYER_H_

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include "network/OnlineRoom.h"
#include "network/OnlineUser.h"
#include "pokerGame/card/Hand.h"
#include "pokerGame/PlayerController.h"

namespace network {

using boost::asio::ip::tcp;

enum SOCKET_READ_STATE {
    RS_WAITING_FOR_NAME,
    RS_WAITING_FOR_PLAY,
    RS_WAITING_FOR_RAISE_BET,
    RS_NOT_WAITING
};

class TelnetPlayer : public pokerGame::PlayerController, public OnlineUser {

public:
    TelnetPlayer(boost::asio::io_service& io_service, OnlineRoom* room);
    ~TelnetPlayer();

    virtual void start();
    virtual tcp::socket& getSocket();

    bool isPlaying() const;

    virtual void seeGamePhase(std::string phaseName);
    virtual void seePlayerTurn(std::string player);
    virtual void seeDealer(std::string dealer);
    virtual void seeBigBlind(std::string player, float bigBlind);
    virtual void seeSmallBlind(std::string player, float smallBlind );
    virtual void seeRoundWinner(std::string winner, float moneyWon);
    virtual void seeWinner(std::string winner);
    virtual void seeOpponentHole(std::string opponent, const pokerGame::card::Hand& hand);
    virtual void seeOpponentMoney(std::string opponent, float money);
    virtual void seeHole(std::vector<pokerGame::card::Card> hole);
    virtual void seeMoney(float money);

    void sendChatMessage(std::string sender, std::string message);
    void seeCardDealt(const pokerGame::card::Hand& hand, const pokerGame::card::Card& new_card);
    virtual pokerGame::Decision makeDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents);

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
