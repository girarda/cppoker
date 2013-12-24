#include "pokerGame/OpponentModel.h"
#include <cmath>
namespace pokerGame {

OpponentModel::OpponentModel(BettingAction lastBettingAction, std::vector<HandContext> handContexts) : numberOfOccurrences(0), handStrengthAverage(0), handStrengthDeviation(0) {
    for (std::vector<HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if(it->hasSameBettingAction(lastBettingAction)) {
            numberOfOccurrences++;
            handStrengthAverage+= it->getHandStrength();
        }
    }
    double variance = 0;
    for (std::vector<HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if(it->hasSameBettingAction(lastBettingAction)) {
            variance += pow(it->getHandStrength()- handStrengthAverage, 2);
        }
    }
    if (numberOfOccurrences != 0) {
        handStrengthDeviation = sqrt(variance/numberOfOccurrences);
    }
}

int OpponentModel::getNumberOfOccurrences() const {
    return numberOfOccurrences;
}

double OpponentModel::getHandStrengthAverage() const {
    return handStrengthAverage;
}

double OpponentModel::getHandStrengthDeviation() const {
    return handStrengthDeviation;
}

}
