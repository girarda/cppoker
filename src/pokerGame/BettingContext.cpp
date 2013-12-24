#include "pokerGame/BettingContext.h"

namespace pokerGame {

BettingContext::BettingContext(BettingRoundType curentBettingRoundType, int nbOfRaises, int nbOfPlayers): bettingRoundType(curentBettingRoundType), numberOfRaises(nbOfRaises), numberOfPlayers(nbOfPlayers) {
}

int BettingContext::getNumberOfRaises() const {
    return numberOfRaises;
}

int BettingContext::getNumberOfPlayers() const {
    return numberOfPlayers;
}

bool BettingContext::operator==(const BettingContext& other) const {
    return this->numberOfPlayers == other.numberOfPlayers && this->numberOfRaises == other.numberOfRaises;
}

}
