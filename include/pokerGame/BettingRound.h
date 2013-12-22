#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include <vector>
#include "pokerGame/Player.h"
#include "GameContext.h"

namespace pokerGame
{

class BettingRound
{
public:
    BettingRound();

    virtual void start(GameContext* gameContext, std::vector<Card> sharedCards);
    virtual float getCurrentMinimumBid() const;

private:
    void playerTurn(Player* player);
    void announcePlayerTurn(Player* player);
    void announcements(Player* player);

    void initialize(GameContext* gameContext, std::vector<Card> sharedCards);

    void nextPlayer();
    int getNextPlayingPlayer(int player);

    bool allPotsAreEven() const;

    GameContext* gameContext;
    std::vector<Card> sharedCards;
    int numberOfRaises;
    int currentPlayer;
};

}

#endif
