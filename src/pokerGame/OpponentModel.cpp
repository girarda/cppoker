#include "pokerGame/OpponentModel.h"
#include <cmath>
namespace pokerGame {

OpponentModel::OpponentModel(BettingContext currentContext, std::vector<HandContext> handContexts) : numberOfOccurrences(0), handStrengthAverage(0), handStrengthDeviation(0) {
    for (std::vector<HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if(it->hasSameBettingContext(currentContext)) {
            numberOfOccurrences++;
            handStrengthAverage+= it->getHandStrength();
        }
    }
    double variance = 0;
    for (std::vector<HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if(it->hasSameBettingContext(currentContext)) {
            variance += pow(it->getHandStrength()- handStrengthAverage, 2);
        }
    }
    handStrengthDeviation = sqrt(variance/numberOfOccurrences);
}

}
