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
    for (std::vector<PokerPlayer*>::iterator it = players.begin(); it != players.end(); it++)
    {
        if (*it)
        {
            delete *it;
        }
    }
}

void GameEngine::start()
{

    announcePhase("Game Start");
    for (PokerPlayer* p: players)
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
    announcePhase("Game End");
    for (PokerPlayer* p: players)
    {
        p->stopPlaying();
    }
}

void GameEngine::playRound()
{
    std::stringstream ss;
    ss << "Round " << numberOfRounds;
    announcePhase(ss.str());
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
    announcePhase("PreFlop");
    distributeOneCard();
    distributeOneCard();
    tableTurn(bet);
}

void GameEngine::flop()
{
    announcePhase("Flop");
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
    announcePhase("Turn");
    announcePhase("River");
    addOneCardToBoard();
    tableTurn(bet);
}

void GameEngine::showdown()
{
    announcePhase("Showdown");
    for (int i = bigBlindPlayerIndex; i < players.size(); i++)
    {
        players[i]->showCards();
    }
    for (int i = 0; i < bigBlindPlayerIndex; i++)
    {
        players[i]->showCards();
    }
    for (PokerPlayer* p : players)
    {
        p->seeOpponentCards(*p);
        p->seeOpponentMoney(*p);
    }
    PokerPlayer* winner = players[0];
    for (PokerPlayer* p: players)
    {
        if (p->hasBetterHand(*winner))
            winner = p;
    }
    winner->winMoney(getTotalPot());
    announceRoundWinner(winner, getTotalPot());
}

void GameEngine::playerTurn(PokerPlayer* player, float minBet)
{
    announcePlayerTurn(player);
    announcements(player);
    if (player->isPlaying())
    {
        Decision d = player->makeDecision(bet, bigBlind);
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

void GameEngine::announcements(PokerPlayer* player)
{
    player->seeDealer(*players[dealerIndex]);
    player->seeBigBlind(*players[bigBlindPlayerIndex], bigBlind);
    player->seeSmallBlind(*players[smallBlindPlayerIndex], bigBlind/2);
    player->seeCards();
    player->seeMoney();

    for (PokerPlayer* p : players)
    {
        player->seeOpponentCards(*p);
        player->seeOpponentMoney(*p);
    }
}

void GameEngine::announcePlayerTurn(PokerPlayer* player)
{
    for (PokerPlayer* p: players)
    {
        p->seePlayerTurn(*player);
    }
}

void GameEngine::announceRoundWinner(PokerPlayer* winner, float moneyWon)
{
    for (PokerPlayer* p: players)
    {
        p->seeRoundWinner(*winner, moneyWon);
    }
}

void GameEngine::announceWinner()
{
    PokerPlayer* winner;
    for (PokerPlayer* p: players)
    {
        if (p->isPlaying())
        {
            winner = p;
            break;
        }
    }
    for (PokerPlayer* p: players)
    {
        p->seeWinner(*winner);
    }
}

void GameEngine::announcePhase(const std::string& phaseName)
{
    for (PokerPlayer* p: players)
    {
        p->seeGamePhase(phaseName);
    }
}

void GameEngine::addPlayer(PokerPlayer* player)
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
    for (PokerPlayer* p: players)
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
    for (PokerPlayer* p: players)
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
    for (PokerPlayer* p: players)
    {
        if (p->isPlaying())
            nbPlayingPlayers++;
    }
    return nbPlayingPlayers;
}

void GameEngine::join(PlayerController* player)
{
    PokerPlayer* newPlayer = new PokerPlayer(player, INITIAL_AMOUNT_OF_MONEY);
    players.push_back(newPlayer);
    sendChatMessage("A new player joined!");
}

void GameEngine::leave(PlayerController* player)
{
    //mVPlayers.erase(player);
}

void GameEngine::sendChatMessage(const std::string& msg)
{
    std::for_each(players.begin(), players.end(),
                  boost::bind(&PokerPlayer::deliver, _1, boost::ref(msg)));
}

}

