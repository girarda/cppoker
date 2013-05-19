#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

namespace pcore
{

    enum HandType {NO_HAND, HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND,
        STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};

    const static int HAND_MAX_CARDS(7);
    const static int HAND_SIZE(5);

    typedef struct HandValue
    {
        HandType type;
        int ranks[HAND_SIZE];
    } HandValue;

    bool operator==(const HandValue &h1, const HandValue &h2);

    const HandValue NO_HAND_VALUE = {
        NO_HAND, {0,0,0,0,0}
    };

    //const static HandValue NO_HAND_VALUE;

    class Hand
    {
        public:
        Hand();
        int getSize() const; 
        void addCard(const pcore::Card &aCard);
        HandValue getHandValue() const;

        bool operator<(const Hand& other) const;
        bool operator>(const Hand& other) const;

        private:
        void calculateBestHand();
        HandValue getHighCardValue() const;
        HandValue getPairValue() const;
        HandValue getTwoPairsValue() const;
        HandValue getThreeOfAKindValue() const;
        HandValue getStraightValue() const;
        HandValue getFlushValue() const;
        HandValue getFullHouseValue() const;
        HandValue getStraightFlushValue() const;

        int size;
        std::vector<Card> cards;
        HandValue bestHand;
    };
    
    bool operator==(const HandValue &h1, const HandValue &h2);
}

#endif
