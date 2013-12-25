#ifndef CONSERVATIVEBETTINGSTRATEGY_H
#define CONSERVATIVEBETTINGSTRATEGY_H

#include "playerController/bot/ContextBasedBettingStrategy.h"

namespace playerController {
namespace bot {

class ConservativeBettingStrategy: public ContextBasedBettingStrategy {
public:
    ConservativeBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy);

    virtual pokerGame::Decision decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount);
};

}
}

#endif
