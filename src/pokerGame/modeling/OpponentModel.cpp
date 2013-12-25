#include "pokerGame/modeling/OpponentModel.h"
#include <cmath>
namespace pokerGame {
namespace modeling {

OpponentModel::OpponentModel(modeling::ActionContext lastActionContext, std::vector<modeling::HandContext> handContexts) : numberOfOccurrences(0), handStrengthAverage(0), handStrengthDeviation(0) {
    for (std::vector<modeling::HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
        if(it->hasSameActionContext(lastActionContext)) {
            numberOfOccurrences++;
            handStrengthAverage+= it->getHandStrength();
        }
    }
    double variance = 0;
    for (std::vector<modeling::HandContext>::iterator it = handContexts.begin(); it != handContexts.end(); it++) {
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

bool OpponentModel::operator==(const OpponentModel& other) const {
    return numberOfOccurrences == other.numberOfOccurrences &&
            handStrengthAverage == other.handStrengthAverage &&
            handStrengthDeviation == other.handStrengthDeviation;
}

}
}
