#include "include/pokerGame/GameRound.h"
#include <iostream>

namespace pokerGame
{

GameRound::GameRound(Deck *deckToUse, BettingRound* bettingRoundToUse): gameContext(0), deck(deckToUse), bettingRound(bettingRoundToUse), sharedCards(), currentPlayer(0)
{
}

void GameRound::playRound(GameContext* gameContext) { // TODO: test this method
    initialize(gameContext);
    betBlinds();

    preFlop();
    if (getNumberOfPlayingPlayers() > 1)
        flop();
    if (getNumberOfPlayingPlayers() > 1)
        turn();
    if (getNumberOfPlayingPlayers() > 1)
        river();
    showdown();
}

void GameRound::initialize(GameContext* gameContext) {
    this->gameContext = gameContext;
    this->currentPlayer = gameContext->dealerIndex;
    deck->shuffle();
        for (Player* p: gameContext->players)
        {
            p->setupForNewRound();
        }
}


void GameRound::betBlinds() {
    std::cout << "blinds bet" << std::endl;
    //std::cout << "big blind is: " << gameContext->bigBlind << " bidded by: " << gameContext->players[gameContext->bigBlindIndex]->getName() << std::endl;
    //std::cout << "small blind is: " << gameContext->bigBlind/2 << " bidded by: " << gameContext->players[gameContext->smallBlindIndex]->getName() << std::endl;
    gameContext->players[gameContext->bigBlindIndex]->addToPot(gameContext->bigBlind);
    gameContext->players[gameContext->smallBlindIndex]->addToPot(gameContext->bigBlind/2);
}

void GameRound::distributeHoles() {
    distributeOneCard();
    distributeOneCard();
}

void GameRound::distributeOneCard() {
    currentPlayer = gameContext->dealerIndex;
    deck->burn();
    do {
        nextPlayer();
        Card c = deck->draw();
        gameContext->players[currentPlayer]->addCardToHole(c);
        //std::cout << "Card " << c.toString() << " was distributed to " << gameContext->players[currentPlayer]->getName() << std::endl;
    } while (currentPlayer != gameContext->dealerIndex);
}

void GameRound::addOneCardToBoard() {
    Card card = deck->draw();
    sharedCards.push_back(card);
    //std::cout << "Card " << card.toString() << " was distributed added to board" << std::endl;
}

void GameRound::preFlop() {
    announcePhase("PreFlop");
    distributeHoles();
    executeNewBettingRound();
}

void GameRound::flop() {
    announcePhase("Flop");
    addOneCardToBoard();
    addOneCardToBoard();
    addOneCardToBoard();
    executeNewBettingRound();
}

void GameRound::turn()
{
    announcePhase("Turn");
    addOneCardToBoard();
    executeNewBettingRound();
}

void GameRound::river()
{
    announcePhase("River");
    addOneCardToBoard();
    executeNewBettingRound();
}

void GameRound::showdown() {
    announcePhase("Showdown");
    for (int i = gameContext->bigBlindIndex; i < gameContext->players.size(); i++)
    {
        gameContext->players[i]->showCards();
    }
    for (int i = 0; i < gameContext->bigBlindIndex; i++)
    {
        gameContext->players[i]->showCards();
    }
    for (Player* p : gameContext->players)
    {
        for(Player* other: gameContext->players) {
            p->seeOpponentHole(*other);
            p->seeOpponentMoney(*other);
        }

    }
    Player* winner = gameContext->players[0];
    for (Player* p: gameContext->players)
    {
        if (p->hasBetterHand(*winner, sharedCards))
            winner = p;
    }
    winner->winMoney(getTotalPot());
    announceRoundWinner(winner, getTotalPot());
}

void GameRound::announcePhase(std::string phaseName) {
    std::cout<< phaseName << std::endl;
    for (Player* p: gameContext->players) {
        p->seeGamePhase(phaseName);
    }
}

void GameRound::announceRoundWinner(Player* winner, float moneyWon) {
    std::cout << "The round winner is " << winner << " who won " << moneyWon << std::endl;
    for (Player* p: gameContext->players) {
        p->seeRoundWinner(*winner, moneyWon);
    }
}

void GameRound::executeNewBettingRound() {
    std::cout << "new betting round" << std::endl;
    bettingRound->start(gameContext, sharedCards);
}

float GameRound::getTotalPot() const {
    float totalPot = 0;
    for (Player* p: gameContext->players)
    {
        totalPot += p->getPot();
    }
    return totalPot;
}

int GameRound::getNumberOfPlayingPlayers() const {
    int nbPlayingPlayers = 0;
    for (Player* p: gameContext->players)
    {
        if (p->isPlaying())
            nbPlayingPlayers++;
    }
    return nbPlayingPlayers;
}

void GameRound::nextPlayer() {
    currentPlayer++;
    if (currentPlayer == gameContext->players.size()) {
        currentPlayer = 0;
    }
    currentPlayer = getNextPlayingPlayer(currentPlayer);

}

int GameRound::getNextPlayingPlayer(int player) {
    int tmp;
    for (tmp = player; tmp < gameContext->players.size(); tmp++) {
        if (gameContext->players[tmp]->isPlaying()) {
            return tmp;
        }
    }
    for (tmp = 0; tmp < player; tmp++) {
        if (gameContext->players[tmp]->isPlaying()) {
            return tmp;
        }
    }
}

}
