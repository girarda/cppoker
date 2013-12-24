#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include <vector>
#include <map>
#include "pokerGame/Player.h"
#include "GameContext.h"
#include "pokerGame/context/ActionContext.h"
#include "pokerGame/BettingRoundType.h"

namespace pokerGame {

class BettingRound {
public:
    BettingRound();

    virtual void start(GameContext* gameContext, std::vector<Card> sharedCards, BettingRoundType bettingRoundType);
    virtual float getCurrentMinimumBid() const;

    virtual std::map<Player*,context::ActionContext> getActionContexts();

private:
    void playerTurn(Player* player);
    void announcePlayerTurn(Player* player);
    void announcements(Player* player);

    void initialize(GameContext* gameContext, std::vector<Card> sharedCards, BettingRoundType bettingRoundType);

    bool allPotsAreEven() const;

    GameContext* gameContext;
    std::vector<Card> sharedCards;
    int numberOfRaises;
    BettingRoundType bettingRoundType;
    std::map<Player*, context::ActionContext> actionContexts;
};

}

#endif
