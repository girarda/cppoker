#include "playerInterface/bot/AgressiveBettingStrategy.h"

namespace playerInterface {
namespace bot {

AgressiveBettingStrategy::AgressiveBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy) : ContextBasedBettingStrategy(handEvaluator, secondBettingStrategy) {
}

pokerGame::Decision AgressiveBettingStrategy::decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount) {
    pokerGame::Decision decision;
    if((double) oppponentsWithBetterEstimatedHandStrength / opponentsModeledCount > 0.5) {
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
