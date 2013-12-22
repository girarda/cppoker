#include "include/pokerGame/GameRound.h"

namespace pokerGame
{

GameRound::GameRound(Deck *deckToUse, BettingRound* bettingRoundToUse): gameContext(0), deck(deckToUse), bettingRound(bettingRoundToUse), sharedCards()
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
    deck->shuffle();
        for (Player* p: gameContext->players)
        {
            p->setupForNewRound();
        }
}


void GameRound::betBlinds() {
    gameContext->players[gameContext->bigBlindIndex]->addToPot(gameContext->bigBlind);
    gameContext->players[gameContext->smallBlindIndex]->addToPot(gameContext->bigBlind/2);
}

void GameRound::distributeHoles() {
    for (int i = gameContext->bigBlindIndex; i < gameContext->players.size(); i++) {
        if (gameContext->players[i]->isPlaying()) {
            Card c1 = deck->draw();
            Card c2 = deck->draw();
            c1.hide();
            gameContext->players[i]->addCardToHole(c1);
            gameContext->players[i]->addCardToHole(c2);
        }
    }
    for (int i = 0; i < gameContext->bigBlindIndex; i++) {
        if (gameContext->players[i]->isPlaying()) {
            Card c1 = deck->draw();
            Card c2 = deck->draw();
            c1.hide();
            gameContext->players[i]->addCardToHole(c1);
            gameContext->players[i]->addCardToHole(c2);
        }
    }
}

void GameRound::addOneCardToBoard() {
    Card card = deck->draw();
    for (int i = gameContext->bigBlindIndex; i < gameContext->players.size(); i++) {
        if (gameContext->players[i]->isPlaying()) {
            sharedCards.push_back(card);
        }
    }
    for (int i = 0; i < gameContext->bigBlindIndex; i++) {
        if (gameContext->players[i]->isPlaying()) {
            sharedCards.push_back(card);
        }
    }
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
    for (Player* p: gameContext->players) {
        p->seeGamePhase(phaseName);
    }
}

void GameRound::announceRoundWinner(Player* winner, float moneyWon) {
    for (Player* p: gameContext->players) {
        p->seeRoundWinner(*winner, moneyWon);
    }
}

void GameRound::executeNewBettingRound() {
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

}
