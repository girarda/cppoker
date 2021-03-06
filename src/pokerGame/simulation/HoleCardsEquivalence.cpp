#include "pokerGame/simulation//HoleCardsEquivalence.h"

namespace pokerGame {
namespace simulation {

HoleCardsEquivalence::HoleCardsEquivalence(int cardValue1, int cardValue2): number1(cardValue1), number2(cardValue2) {
}

int HoleCardsEquivalence::getNumber1() const {
    return number1;
}

int HoleCardsEquivalence::getNumber2() const {
    return number2;
}

std::vector<card::Card> HoleCardsEquivalence::equivalenceToCards() const {
    std::vector<card::Card> cards;
    card::Card c1(this->number1, card::SPADE);
    cards.push_back(c1);
    if (number1 == number2) {
        card::Card c2(this->number2, card::HEART);
        cards.push_back(c2);
    } else {
        card::Card c2(this->number2, card::SPADE);
        cards.push_back(c2);
    }
    return cards;
}

}
}
