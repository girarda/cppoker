#include "pokerGame/BettingContext.h"

namespace pokerGame {

BettingContext::BettingContext(BettingRoundType curentBettingRoundType, int nbOfRaises, int nbOfPlayers): bettingRoundType(curentBettingRoundType) {
    numberOfRaises = valueFor(nbOfRaises);
    numberOfPlayers = valueFor(nbOfPlayers);
}

Quantity BettingContext::getNumberOfRaises() const {
    return numberOfRaises;
}

Quantity BettingContext::getNumberOfPlayers() const {
    return numberOfPlayers;
}

bool BettingContext::operator==(const BettingContext& other) const {
    return this->numberOfPlayers == other.numberOfPlayers && this->numberOfRaises == other.numberOfRaises;
}

Quantity BettingContext::valueFor(int number) {
    if (number < 3) {
        return FEW;
    } else {
        return MANY;
    }
}


}
