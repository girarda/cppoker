#include "pokerGame/GameEngine.h"
#include <algorithm>
#include "boost/bind.hpp"
#include "boost/thread.hpp"

namespace pokerGame
{

GameEngine::GameEngine():
    players(),
    bigBlind(2),
    bigBlindPlayerIndex(-1),
    smallBlindPlayerIndex(-1),
    dealerIndex(-1),
    bet(0),
    INITIAL_AMOUNT_OF_MONEY(10)
{
}

GameEngine::~GameEngine()
{
    for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++)
    {
        if (*it)
        {
            delete *it;
        }
    }
}

void GameEngine::start()
{
    for (Player* p: players)
    {
        p->startPlaying();
    }
    while(getNumberOfPlayingPlayers() > 1)
    {
        tableTurn();
        if (numberTableTurns % 2 == 0)
            bigBlind *= 2;
    }
    announceWinner();
}

void GameEngine::tableTurn()
{
    initTableTurn();

    betBlinds();

    preFlop();
    if (getNumberOfPlayingPlayers() > 1)
        flop();
    if (getNumberOfPlayingPlayers() > 1)
        turn();
    if (getNumberOfPlayingPlayers() > 1)
        river();
    showdown();

//    numberTableTurns++;
}

void GameEngine::preFlop()
{
    for (Player* p: players)
    {
        p->addCard(deck.draw());
        p->addCard(deck.draw());
    }
    playRound(bet);
}

void GameEngine::flop()
{
    Card c1 = deck.draw();
    Card c2 = deck.draw();
    Card c3 = deck.draw();
    for (Player* p: players)
    {
        p->addCard(c1);
        p->addCard(c2);
        p->addCard(c3);
    }
    playRound(bet);
}

void GameEngine::turn()
{
    Card c1 = deck.draw();
    for (Player* p: players)
    {
        p->addCard(c1);
    }
    playRound(bet);
}

void GameEngine::river()
{
    Card c1 = deck.draw();
    for (Player* p: players)
    {
        p->addCard(c1);
    }
    playRound(bet);
}

void GameEngine::showdown()
{
    Player* winner = players[0];
    for (Player* p: players)
    {
        if (p->hasBetterHand(*winner))
            winner = p;
    }
    winner->winMoney(getTotalPot());
    announceWinner();
}

void GameEngine::playerTurn(Player* player, float minBet)
{
    announcements(player);
    if (player->isPlaying())
    {
        Decision d = player->makeDecision(bet);
        if (d.choice == CALL)
        {
            bet = d.bet;
        }
    }
}

void GameEngine::announcements(Player* player)
{
    player->seeDealer(*players[dealerIndex]);
    player->seeBigBlind(*players[bigBlindPlayerIndex], bigBlind);
    player->seeSmallBlind(*players[smallBlindPlayerIndex], bigBlind/2);
    player->seeCards();
    player->seeMoney();

    for (Player* p : players)
    {
        player->seeOpponentCards(*p);
        player->seeOpponentMoney(*p);
    }
}

void GameEngine::announceWinner()
{
    Player* winner;
    for (Player* p: players)
    {
        if (p->isPlaying())
        {
            winner = p;
            break;
        }
    }
    for (Player* p: players)
    {
        p->seeWinner(*winner);
    }
}

void GameEngine::addPlayer(Player* player)
{
    players.push_back(player);
}

void GameEngine::playRound(float minBet)
{
    for (Player* p: players)
    {
        playerTurn(p, minBet);
    }
}

void GameEngine::initTableTurn()
{
    chooseNextDealer();
    bet = bigBlind;
    deck.shuffle();
    for (Player* p: players)
    {
        p->setupForNewTableTurn();
    }
}

void GameEngine::chooseNextDealer()
{
    dealerIndex = 0;
    bigBlindPlayerIndex = 0;
    smallBlindPlayerIndex = 0;
}

void GameEngine::betBlinds()
{
    players[bigBlindPlayerIndex]->addToPot(bigBlind);
    players[smallBlindPlayerIndex]->addToPot(bigBlind/2);
}

float GameEngine::getTotalPot()
{
    float totalPot = 0;
    for (Player* p: players)
    {
        totalPot += p->getPot();
    }
    return totalPot;
}

int GameEngine::    getNumberOfPlayers() const
{
    return players.size();
}

int GameEngine::getNumberOfPlayingPlayers() const
{
    int nbPlayingPlayers = 0;
    for (Player* p: players)
    {
        if (p->isPlaying())
            nbPlayingPlayers++;
    }
    return nbPlayingPlayers;
}

void GameEngine::join(IPlayer* player)
{
    Player* newPlayer = new Player(player, INITIAL_AMOUNT_OF_MONEY);
    players.push_back(newPlayer);
    sendChatMessage("A new player joined!");
    //if (players.size() == 2)
    //    start();
}

void GameEngine::leave(IPlayer* player)
{
    //mVPlayers.erase(player);
}

void GameEngine::sendChatMessage(const std::string& msg)
{
    std::for_each(players.begin(), players.end(),
                  boost::bind(&Player::deliver, _1, boost::ref(msg)));
//    if (msg == "Chat: alex: play\r\n")
//        start();
}

}

