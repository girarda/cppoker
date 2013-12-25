#ifndef AGRESSIVEBETTINGSTRATEGY_H
#define AGRESSIVEBETTINGSTRATEGY_H

#include "playerController/bot/ContextBasedBettingStrategy.h"

namespace playerController {
namespace bot {

class AgressiveBettingStrategy: public ContextBasedBettingStrategy {
public:
    AgressiveBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy);

    virtual pokerGame::Decision decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount);
};

}
}

#endif
