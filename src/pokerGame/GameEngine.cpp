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
        playRound();
        if (numberOfRounds % 2 == 0)
            bigBlind *= 2;
    }
    announceWinner();
    endGame();
}

void GameEngine::endGame()
{
    for (Player* p: players)
    {
        p->stopPlaying();
    }
}

void GameEngine::playRound()
{
    initRound();

    betBlinds();

    preFlop();
    if (getNumberOfPlayingPlayers() > 1)
        flop();
    if (getNumberOfPlayingPlayers() > 1)
        turn();
    if (getNumberOfPlayingPlayers() > 1)
        river();
    showdown();

    numberOfRounds++;
}

void GameEngine::preFlop()
{
    distributeOneCard();
    distributeOneCard();
    tableTurn(bet);
}

void GameEngine::flop()
{
    addOneCardToBoard();
    addOneCardToBoard();
    addOneCardToBoard();
    tableTurn(bet);
}

void GameEngine::turn()
{
    addOneCardToBoard();
    tableTurn(bet);
}

void GameEngine::river()
{
    addOneCardToBoard();
    tableTurn(bet);
}

void GameEngine::showdown()
{
    for (int i = bigBlindPlayerIndex; i < players.size(); i++)
    {
        players[i]->showCards();
    }
    for (int i = 0; i < bigBlindPlayerIndex; i++)
    {
        players[i]->showCards();
    }
    for (Player* p : players)
    {
        p->seeOpponentCards(*p);
        p->seeOpponentMoney(*p);
    }
    Player* winner = players[0];
    for (Player* p: players)
    {
        if (p->hasBetterHand(*winner))
            winner = p;
    }
    winner->winMoney(getTotalPot());
    announceRoundWinner(winner, getTotalPot());
}

void GameEngine::playerTurn(Player* player, float minBet)
{
    announcements(player);
    if (player->isPlaying())
    {
        Decision d = player->makeDecision(bet);
        if (d.choice == CALL)
        {
            bet += d.bet;
        }
    }
}

void GameEngine::distributeOneCard()
{
    for (int i = bigBlindPlayerIndex; i < players.size(); i++)
    {
        Card card = deck.draw();
        players[i]->addCard(card);
    }
    for (int i = 0; i < bigBlindPlayerIndex; i++)
    {
        Card card = deck.draw();
        players[i]->addCard(card);
    }
}

void GameEngine::addOneCardToBoard()
{
    Card card = deck.draw();
    for (int i = bigBlindPlayerIndex; i < players.size(); i++)
    {
        players[i]->addCard(card);
    }
    for (int i = 0; i < bigBlindPlayerIndex; i++)
    {
        players[i]->addCard(card);
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

void GameEngine::announceRoundWinner(Player* winner, float moneyWon)
{
    for (Player* p: players)
    {
        p->seeRoundWinner(*winner, moneyWon);
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

void GameEngine::tableTurn(float minBet)
{
    float currentBet;
    do {
        currentBet = bet;
        for (int i = bigBlindPlayerIndex; i < players.size(); i++)
        {
            playerTurn(players[i], minBet);
        }
        for (int i = 0; i < bigBlindPlayerIndex; i++)
        {
            playerTurn(players[i], minBet);
        }
    } while (bet != currentBet);
}

void GameEngine::initRound()
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
    dealerIndex++;
    dealerIndex %= players.size();

    bigBlindPlayerIndex = dealerIndex+1;
    bigBlindPlayerIndex %= players.size();

    smallBlindPlayerIndex = dealerIndex+2;
    smallBlindPlayerIndex %= players.size();
}

void GameEngine::betBlinds()
{
    players[bigBlindPlayerIndex]->addToPot(bigBlind);
    players[smallBlindPlayerIndex]->addToPot(bigBlind/2);
}

float GameEngine::getTotalPot() const
{
    float totalPot = 0;
    for (Player* p: players)
    {
        totalPot += p->getPot();
    }
    return totalPot;
}

int GameEngine::getNumberOfPlayers() const
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
}

void GameEngine::leave(IPlayer* player)
{
    //mVPlayers.erase(player);
}

void GameEngine::sendChatMessage(const std::string& msg)
{
    std::for_each(players.begin(), players.end(),
                  boost::bind(&Player::deliver, _1, boost::ref(msg)));
}

}

