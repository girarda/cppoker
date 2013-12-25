#ifndef AGRESSIVEBETTINGSTRATEGY_H
#define AGRESSIVEBETTINGSTRATEGY_H

#include "playerInterface/bot/ContextBasedBettingStrategy.h"

namespace playerInterface {
namespace bot {

class AgressiveBettingStrategy: public ContextBasedBettingStrategy {
public:
    AgressiveBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy);

    virtual pokerGame::Decision decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount);
};

}
}

#endif
