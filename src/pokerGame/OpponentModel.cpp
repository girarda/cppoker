#include "pokerGame/OpponentModel.h"
#include <cmath>
namespace pokerGame {

OpponentModel::OpponentModel(context::ActionContext lastActionContext, std::vector<context::HandContext> handContexts) : numberOfOccurrences(0), handStrengthAverage(0), handStrengthDeviation(0) {
    for (std::vector<context::HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if(it->hasSameActionContext(lastActionContext)) {
            numberOfOccurrences++;
            handStrengthAverage+= it->getHandStrength();
        }
    }
    double variance = 0;
    for (std::vector<context::HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if(it->hasSameActionContext(lastActionContext)) {
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
