#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include <vector>
#include <map>
#include "pokerGame/Player.h"
#include "GameContext.h"
#include "pokerGame/modeling/ActionContext.h"
#include "pokerGame/BettingRoundType.h"

namespace pokerGame {

class BettingRound {
public:
    BettingRound();

    virtual void start(GameContext* gameContext, const std::vector<card::Card> &sharedCards, const BettingRoundType &bettingRoundType);
    virtual float getCurrentMaximumBid() const;

    virtual std::map<Player*,modeling::ActionContext> getActionContexts();

private:
    void playerTurn(Player* player);
    void play(Player* player);
    void announcePlayerTurn(Player* player);
    void announcements(Player* player);

    void initialize(GameContext* gameContext, const std::vector<card::Card> &sharedCards, const BettingRoundType &bettingRoundType);

    bool allPotsAreEven() const;

    GameContext* gameContext;
    std::vector<card::Card> sharedCards;
    int numberOfRaises;
    BettingRoundType bettingRoundType;
    std::map<Player*, modeling::ActionContext> actionContexts;
};

}

#endif
