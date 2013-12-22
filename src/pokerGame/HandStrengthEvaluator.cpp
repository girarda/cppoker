#include "pokerGame/HandStrengthEvaluator.h"
#include "pokerGame/Deck.h"
#include "pokerGame/Hand.h"
#include <cmath>

namespace pokerGame {

HandStrengthEvaluator::HandStrengthEvaluator() {
}

HandStrengthEvaluator::~HandStrengthEvaluator() {
}

double HandStrengthEvaluator::evaluate(std::vector<Card> hole, std::vector<Card> sharedCards, int numberOfPlayers) {
    int wins = 0;
    int losses = 0;
    int ties = 0;
    Deck deck;
    for(Card c: hole) {
        deck.removeCard(c);
    }
    for(Card c: sharedCards) {
        deck.removeCard(c);
    }

    std::vector<std::vector<Card> > couples = deck.toCouples();

    Hand playerHand(hole, sharedCards);
    for(std::vector<Card> couple: couples) {
        Hand opponentHand(couple, sharedCards);
        if (playerHand < opponentHand) {
            losses++;
        } else if(playerHand == opponentHand) {
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

}
