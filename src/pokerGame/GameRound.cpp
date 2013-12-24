#include "include/pokerGame/GameRound.h"
#include <iostream>

namespace pokerGame {

GameRound::GameRound(Deck *deckToUse, BettingRound* bettingRoundToUse): gameContext(0), deck(deckToUse), bettingRound(bettingRoundToUse), sharedCards(), handEvaluator() {
}

void GameRound::playRound(GameContext* gameContext) { // TODO: test this method
    initialize(gameContext);
    betBlinds();

    preFlop();
    if (getNumberOfPlayingPlayers() > 1) {
        flop();
    }
    if (getNumberOfPlayingPlayers() > 1) {
        turn();
    }
    if (getNumberOfPlayingPlayers() > 1) {
        river();
    }
    showdown();
}

void GameRound::initialize(GameContext* gameContext) {
    this->gameContext = gameContext;
    this->gameContext->setCurrentPlayerDealer();
    deck->shuffle();
    for (Player* p: gameContext->getPlayers()) {
        p->setupForNewRound();
    }
}


void GameRound::betBlinds() {
    //std::cout << "blinds bet" << std::endl;
    //std::cout << "big blind is: " << gameContext->bigBlind << " bidded by: " << gameContext->players[gameContext->bigBlindIndex]->getName() << std::endl;
    //std::cout << "small blind is: " << gameContext->bigBlind/2 << " bidded by: " << gameContext->players[gameContext->smallBlindIndex]->getName() << std::endl;
    gameContext->getPlayers()[gameContext->getBigBlindIndex()]->addToPot(gameContext->getBigBlind());
    gameContext->getPlayers()[gameContext->getSmallBlindIndex()]->addToPot(gameContext->getBigBlind()/2);
}

void GameRound::distributeHoles() {
    distributeOneCard();
    distributeOneCard();
}

void GameRound::distributeOneCard() {
    gameContext->setCurrentPlayerDealer();
    deck->burn();
    do {
        gameContext->nextPlayer();
        Card c = deck->draw();
        gameContext->getCurrentPlayer()->addCardToHole(c);
        //std::cout << "Card " << c.toString() << " was distributed to " << gameContext->players[currentPlayer]->getName() << std::endl;
    } while (gameContext->getCurrentPlayerIndex() != gameContext->getDealerIndex());
}

void GameRound::addOneCardToBoard() {
    Card card = deck->draw();
    sharedCards.push_back(card);
    //std::cout << "Card " << card.toString() << " was distributed added to board" << std::endl;
}

void GameRound::preFlop() {
    announcePhase("PreFlop");
    distributeHoles();
    executeNewBettingRound(PRE_FLOP);
}

void GameRound::flop() {
    announcePhase("Flop");
    addOneCardToBoard();
    addOneCardToBoard();
    addOneCardToBoard();
    executeNewBettingRound(POST_FLOP);
}

void GameRound::turn() {
    announcePhase("Turn");
    addOneCardToBoard();
    executeNewBettingRound(POST_TURN);
}

void GameRound::river() {
    announcePhase("River");
    addOneCardToBoard();
    executeNewBettingRound(POST_RIVER);
}

void GameRound::showdown() {
    announcePhase("Showdown");
    Player* winner = getWinner();
    winner->winMoney(getTotalPot());
    announceRoundWinner(winner, getTotalPot());

    std::map<Player*, std::vector<BettingAction> > bettingActions;
    for (std::map<Player*, std::vector<BettingAction> >::iterator it = bettingRound->getBettingActions().begin(); it != bettingRound->getBettingActions().end(); it++) {
        if (it->first->isPlaying()) {
            bettingActions.insert(*it);
        }
    }
    for (std::map<Player*, std::vector<BettingAction> >::iterator it = bettingActions.begin(); it != bettingActions.end(); it++) {
        gameContext->addHandContext(it->first, it->second, handEvaluator.evaluate(it->first->getVisibleHole(), sharedCards, gameContext->getNumberOfPlayingPlayers()));
    }
}

void GameRound::announcePhase(std::string phaseName) {
    //std::cout<< phaseName << std::endl;
    for (Player* p: gameContext->getPlayers()) {
        p->seeGamePhase(phaseName);
    }
}

void GameRound::announceRoundWinner(Player* winner, float moneyWon) {
    //std::cout << "The round winner is " << winner << " who won " << moneyWon << std::endl;
    for (Player* p: gameContext->getPlayers()) {
        p->seeRoundWinner(*winner, moneyWon);
    }
}

void GameRound::executeNewBettingRound(BettingRoundType bettingRoundType) {
    //std::cout << "new betting round" << std::endl;
    bettingRound->start(gameContext, sharedCards, bettingRoundType);
}

float GameRound::getTotalPot() const {
    float totalPot = 0;
    for (Player* p: gameContext->getPlayers()) {
        totalPot += p->getPot();
    }
    return totalPot;
}

int GameRound::getNumberOfPlayingPlayers() const {
    int nbPlayingPlayers = 0;
    for (Player* p: gameContext->getPlayers()) {
        if (p->isPlaying()) {
            nbPlayingPlayers++;
        }
    }
    return nbPlayingPlayers;
}

Player* GameRound::getWinner() {
    for (int i = gameContext->getBigBlindIndex(); i < gameContext->getPlayers().size(); i++) {
        gameContext->getPlayers()[i]->showCards();
    }
    for (int i = 0; i < gameContext->getBigBlindIndex(); i++) {
        gameContext->getPlayers()[i]->showCards();
    }
    for (Player* p : gameContext->getPlayers()) {
        for(Player* other: gameContext->getPlayers()) {
            p->seeOpponentHole(*other);
            p->seeOpponentMoney(*other);
        }
    }
    Player* winner = gameContext->getPlayers()[0];
    for (Player* p: gameContext->getPlayers()) {
        if (p->hasBetterHand(*winner, sharedCards)) {
            winner = p;
        }
    }
    return winner;
}

}
