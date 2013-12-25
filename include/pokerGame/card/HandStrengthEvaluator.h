#ifndef HANDSTRENGTHEVALUATOR_H
#define HANDSTRENGTHEVALUATOR_H

#include<vector>
#include"Card.h"
#include "pokerGame/card/Deck.h"
#include "pokerGame/card/Hand.h"

namespace pokerGame {
namespace card {

class HandStrengthEvaluator {
public:
    HandStrengthEvaluator();
    virtual ~HandStrengthEvaluator();
    virtual double evaluate(const std::vector<Card> &holeCards, const std::vector<Card> &sharedCards, int numberOfPlayers);

private:
    double evaluateHandStrength(const Deck& deck, const std::vector<Card> &holeCards, const std::vector<Card> &sharedCards, int numberOfPlayers);
    double calculateHandStrength(int wins, int ties, int losses, int numberOfPlayers);
    Deck getDeckWithoutRemovedCards(const std::vector<Card> &holeCards, const std::vector<Card> &sharedCards);
    void removeCards(Deck& deck, const std::vector<Card> &cards);

};

}
}

#endif
