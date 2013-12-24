#ifndef AGRESSIVEBETTINGSTRATEGY_H
#define AGRESSIVEBETTINGSTRATEGY_H

#include "playerInterface/bot/ContextBasedBettingStrategy.h"

namespace playerInterface {
namespace bot {

class AgressiveBettingStrategy: public ContextBasedBettingStrategy {
public:
    AgressiveBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy);

    virtual pokerGame::Decision decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount);
};

}
}

#endif
