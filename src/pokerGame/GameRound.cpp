#include "include/pokerGame/GameRound.h"

namespace pokerGame
{

GameRound::GameRound(Deck *deckToUse, BettingRound* bettingRoundToUse): players(), bigBlind(0), dealerIndex(0), bigBlindIndex(0), smallBlindIndex(0), deck(deckToUse), bettingRound(bettingRoundToUse)
{
}

void GameRound::playRound(std::vector<PokerPlayer*> players, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex) { // TODO: test this method
    initialize(players, blind, dealerPlayerIndex, bigBlindPlayerIndex, smallBlindPlayerIndex);
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

void GameRound::initialize(std::vector<PokerPlayer*> players, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex) {
    this->players = players;
    this->bigBlind = blind;
    this->dealerIndex = dealerPlayerIndex;
    this->bigBlindIndex = bigBlindPlayerIndex;
    this->smallBlindIndex = smallBlindPlayerIndex;
    deck->shuffle();
        for (PokerPlayer* p: players)
        {
            p->setupForNewRound();
        }
}


void GameRound::betBlinds() {
    players[bigBlindIndex]->addToPot(bigBlind);
    players[smallBlindIndex]->addToPot(bigBlind/2);
}

void GameRound::distributeHoles() {
    for (int i = bigBlindIndex; i < players.size(); i++) {
        if (players[i]->isPlaying()) {
            Card c1 = deck->draw();
            Card c2 = deck->draw();
            c1.hide();
            players[i]->addCard(c1);
            players[i]->addCard(c2);
        }
    }
    for (int i = 0; i < bigBlindIndex; i++) {
        if (players[i]->isPlaying()) {
            Card c1 = deck->draw();
            Card c2 = deck->draw();
            c1.hide();
            players[i]->addCard(c1);
            players[i]->addCard(c2);
        }
    }
}

void GameRound::addOneCardToBoard() {
    Card card = deck->draw();
    for (int i = bigBlindIndex; i < players.size(); i++) {
        if (players[i]->isPlaying()) {
            players[i]->addCard(card);
        }
    }
    for (int i = 0; i < bigBlindIndex; i++) {
        if (players[i]->isPlaying()) {
            players[i]->addCard(card);
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
    for (int i = bigBlindIndex; i < players.size(); i++)
    {
        players[i]->showCards();
    }
    for (int i = 0; i < bigBlindIndex; i++)
    {
        players[i]->showCards();
    }
    for (PokerPlayer* p : players)
    {
        for(PokerPlayer* other: players) {
            p->seeOpponentCards(*other);
            p->seeOpponentMoney(*other);
        }

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

void GameRound::announcePhase(std::string phaseName) {
    for (PokerPlayer* p: players) {
        p->seeGamePhase(phaseName);
    }
}

void GameRound::announceRoundWinner(PokerPlayer* winner, float moneyWon) {
    for (PokerPlayer* p: players) {
        p->seeRoundWinner(*winner, moneyWon);
    }
}

void GameRound::executeNewBettingRound() {
    bettingRound->start(players, bigBlind, dealerIndex, bigBlindIndex, smallBlindIndex);
}

float GameRound::getTotalPot() const {
    float totalPot = 0;
    for (PokerPlayer* p: players)
    {
        totalPot += p->getPot();
    }
    return totalPot;
}

int GameRound::getNumberOfPlayingPlayers() const {
    int nbPlayingPlayers = 0;
    for (PokerPlayer* p: players)
    {
        if (p->isPlaying())
            nbPlayingPlayers++;
    }
    return nbPlayingPlayers;
}

}
