#include "pokerGame/card/HandStrengthEvaluator.h"
#include <cmath>

namespace pokerGame {
namespace card {

HandStrengthEvaluator::HandStrengthEvaluator() {
}

HandStrengthEvaluator::~HandStrengthEvaluator() {
}

double HandStrengthEvaluator::evaluate(const std::vector<Card> &holeCards, const std::vector<Card> &sharedCards, int numberOfPlayers) {
    Deck deck = getDeckWithoutRemovedCards(holeCards, sharedCards);
    return evaluateHandStrength(deck, holeCards, sharedCards, numberOfPlayers);
}

double HandStrengthEvaluator::evaluateHandStrength(const Deck &deck, const std::vector<Card> &holeCards, const std::vector<Card> &sharedCards, int numberOfPlayers) {
    int losses, ties, wins = 0;
    Hand hand(holeCards, sharedCards);
    std::vector<std::vector<Card> > couples = deck.toCouples();
    for(std::vector<Card> couple: couples) {
        Hand opponentHand(couple, sharedCards);
        if (hand < opponentHand) {
            losses++;
        } else if(hand == opponentHand) {
            ties++;
        } else {
            wins++;
        }
    }
    return calculateHandStrength(wins, ties, losses, numberOfPlayers);
}

double HandStrengthEvaluator::calculateHandStrength(int wins, int ties, int losses, int numberOfPlayers) {
    double numberOfWins = (wins + 0.5* ties);
    double totalNumber = (wins + losses + ties);
    return pow(numberOfWins/totalNumber, numberOfPlayers);
}

Deck HandStrengthEvaluator::getDeckWithoutRemovedCards(const std::vector<Card> &holeCards, const std::vector<Card> &sharedCards) {
    Deck deck;
    removeCards(deck, holeCards);
    removeCards(deck, sharedCards);
    return deck;
}

void HandStrengthEvaluator::removeCards(Deck& deck, const std::vector<Card> &cards)
{
    for(Card c: cards) {
        deck.removeCard(c);
    }
}


}
}
