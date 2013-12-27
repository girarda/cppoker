#include "pokerGame/modeling/BettingContext.h"

namespace pokerGame {
namespace modeling {

BettingContext::BettingContext(const BettingRoundType &curentBettingRoundType, int nbOfRaises, int nbOfPlayers): bettingRoundType(curentBettingRoundType), numberOfRaises(nbOfRaises), numberOfPlayers(nbOfPlayers) {
}

int BettingContext::getNumberOfRaises() const {
    return numberOfRaises;
}

int BettingContext::getNumberOfPlayers() const {
    return numberOfPlayers;
}

bool BettingContext::hasManyRaises() const {
    return numberOfRaises >= MANY_THRESHOLD;
}

bool BettingContext::hasManyPlayers() const {
    return numberOfPlayers >= MANY_THRESHOLD;
}

BettingRoundType BettingContext::getBettingRoundType() const {
    return bettingRoundType;
}

bool BettingContext::operator==(const BettingContext& other) const {
    return this->numberOfPlayers == other.numberOfPlayers && this->numberOfRaises == other.numberOfRaises;
}

const int BettingContext::MANY_THRESHOLD(3);

}
}
