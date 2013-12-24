#include "playerInterface/bot/ConservativeBettingStrategy.h"

namespace playerInterface {
namespace bot {

ConservativeBettingStrategy::ConservativeBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy) : ContextBasedBettingStrategy(handEvaluator, secondBettingStrategy) {
}

pokerGame::Decision ConservativeBettingStrategy::decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount) {
    pokerGame::Decision decision;
    if(oppponentsWithBetterEstimatedHandStrength == 0) {
        decision.choice = pokerGame::RAISE;
        decision.bet = minBet + bigBlind;
    } else if(minBet == 0) {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    } else {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

}
}
