#include "include/pokerGame/HoleCardsEquivalence.h"

namespace pokerGame {

HoleCardsEquivalence::HoleCardsEquivalence(int cardValue1, int cardValue2): number1(cardValue1), number2(cardValue2) {
}

int HoleCardsEquivalence::getNumber1() const {
    return number1;
}

int HoleCardsEquivalence::getNumber2() const {
    return number2;
}

std::vector<Card> HoleCardsEquivalence::equivalenceToCards() const {
    std::vector<Card> cards;
    Card c1(this->number1, SPADE);
    cards.push_back(c1);
    if (number1 == number2) {
        Card c2(this->number2, HEART);
        cards.push_back(c2);
    } else {
        Card c2(this->number2, SPADE);
        cards.push_back(c2);
    }
    return cards;
}


}
