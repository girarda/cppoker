#ifndef GAMEROUND_H
#define GAMEROUND_H

#include <vector>
#include "pokerGame/Player.h"
#include "pokerGame/card/Deck.h"
#include "pokerGame/BettingRound.h"
#include "GameContext.h"
#include "BettingRoundType.h"
#include "pokerGame/card/HandStrengthEvaluator.h"
#include "gtest/gtest_prod.h"

namespace pokerGame {

class GameRound {
public:
    GameRound(card::Deck *deckToUse, BettingRound* bettingRoundToUse);

    virtual void playRound(GameContext* gameContext);

    Player* getWinner();

protected:
    virtual void distributeHoles();
    void distributeOneCard();

    card::Deck* deck;
    GameContext* gameContext;

private:
    std::vector<card::Card> sharedCards;
    BettingRound* bettingRound;
    card::HandStrengthEvaluator handEvaluator;
    std::map<Player*, std::vector<modeling::ActionContext> > bettingActions;

    void initialize(GameContext* gameContext);

    void betBlinds();
    void addOneCardToBoard();

    void preFlop();
    void flop();
    void turn();
    void river();
    void showdown();

    void announcePhase(std::string phaseName);
    void announceRoundWinner(Player* winner, float moneyWon);

    float getTotalPot() const;

    void executeNewBettingRound(const BettingRoundType &bettingRoundType);
    int getNumberOfPlayingPlayers() const;

    void saveShowdownedHandsToContext();

    FRIEND_TEST(GameRoundTest,bigAndSmallBlindPlayersAddTheirBlindsToTheirPotWhenBettingPot);
    FRIEND_TEST(GameRoundTest,twoCardsAreAddedToEachPlayingPlayersHoleWhenDistributingHoles);
    FRIEND_TEST(GameRoundTest,holesAreNotDistributedToPlayersWhoAreNotPlaying);
    FRIEND_TEST(GameRoundTest,addingACardToTheBoardAddsOneCardToEveryPlayingPlayer);
    FRIEND_TEST(GameRoundTest,everyPlayerSeePhaseNameWhenAnnouncingPhase);
    FRIEND_TEST(GameRoundTest,everyPlayerSeeWinnerWhenAnnouncingRoundWinner);
    FRIEND_TEST(GameRoundTest,preFlopPhaseIsAnnouncedWhenItBegins);
    FRIEND_TEST(GameRoundTest,twoCardsAreDistributedInPreFlop);
    FRIEND_TEST(GameRoundTest,flopPhaseIsAnnouncedWhenItBegins);
    FRIEND_TEST(GameRoundTest,threeCardsAreAddedToBoardInFlop);
    FRIEND_TEST(GameRoundTest,turnPhaseIsAnnouncedWhenItBegins);
    FRIEND_TEST(GameRoundTest,oneCardsAreAddedToBoardInTurn);
    FRIEND_TEST(GameRoundTest,riverPhaseIsAnnouncedWhenItBegins);
    FRIEND_TEST(GameRoundTest,oneCardsAreAddedToBoardInRiver);
    FRIEND_TEST(GameRoundTest,showdownPhaseIsAnnouncedWhenItBegins);
    FRIEND_TEST(GameRoundTest,theRoundWinnerWinsThePot);
    FRIEND_TEST(GameRoundTest,theRoundWinnerIsAnnouncedInShowndown);
    FRIEND_TEST(GameRoundTest,everyPlayersShowTheirCardsInShowdown);
    FRIEND_TEST(GameRoundTest,everyPlayersSeeTheirOponnentsCardsAndMoney);
    FRIEND_TEST(GameRoundTest,aBettingRoundStartsWhenExecutingNewBettingRound);
    FRIEND_TEST(GameRoundTest,getNumberOfPlayingPlayersReturnsTheNumberOfPlayingPlayers);
    FRIEND_TEST(GameRoundTest,deckIsShuffledWhenInitializingTheRound);
    FRIEND_TEST(GameRoundTest,everyPlayersSetupForNewRoundWhenInitializingGameRound);
};

}

#endif
