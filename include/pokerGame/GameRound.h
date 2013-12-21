#ifndef GAMEROUND_H
#define GAMEROUND_H

#include <vector>
#include "pokerGame/PokerPlayer.h"
#include "Deck.h"
#include "BettingRound.h"
#include "gtest/gtest_prod.h"

namespace pokerGame
{

class GameRound
{
public:
    GameRound(Deck *deckToUse, BettingRound* bettingRoundToUse);

    virtual void playRound(std::vector<PokerPlayer*> players, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex);

private:
    int dealerIndex;
    int bigBlindIndex;
    int smallBlindIndex;

    float bigBlind;

    std::vector<PokerPlayer*> players;

    Deck* deck;
    BettingRound* bettingRound;

    void initialize(std::vector<PokerPlayer*> players, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex);

    void betBlinds();
    void distributeHoles();
    void addOneCardToBoard();

    void preFlop();
    void flop();
    void turn();
    void river();
    void showdown();

    void announcePhase(std::string phaseName);
    void announceRoundWinner(PokerPlayer* winner, float moneyWon);

    float getTotalPot() const;

    void executeNewBettingRound();
    int getNumberOfPlayingPlayers() const;

    FRIEND_TEST(GameRoundTest,bigAndSmallBlindPlayersAddTheirBlindsToTheirPotWhenBettingPot);
    FRIEND_TEST(GameRoundTest,twoCardIsAddedToEachPlayingPlayerWhenDistributingHoles);
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
