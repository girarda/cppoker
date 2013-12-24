#ifndef CONSERVATIVEBETTINGSTRATEGY_H
#define CONSERVATIVEBETTINGSTRATEGY_H

#include "playerInterface/bot/ContextBasedBettingStrategy.h"

namespace playerInterface {
namespace bot {

class ConservativeBettingStrategy: public ContextBasedBettingStrategy {
public:
    ConservativeBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy);

    virtual pokerGame::Decision decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount);
};

}
}

#endif
