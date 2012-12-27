/**-------------------------/// Hand.h \\\---------------------------
 *
 * <b>Hand.h</b>
 * @version : 1.0
 * @since : 2012 Aug 31
 *
 * @description :
 *     Interface of the Hand class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO :
 *
 *--------------------------\\\ Hand.h ///---------------------------*/

#ifndef HAND_H
#define HAND_H

#include "Deck.h"
#include <map>

namespace pcore
{
    const int HAND_MAX_CARDS(7);
    const int HAND_SIZE(5);

    enum HandType {NO_HAND, PAIR, TWO_PAIR, THREE_OF_A_KIND,
        STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH};

    typedef struct HandValue
    {
        HandType type;
        int ranks[HAND_SIZE];
    } HandValue;

    class Hand
    {
    public:
        Hand();
        
        void addCard(const Card &newCard);
        const HandValue& getValue() const;
        void empty();
        size_t getCount() const;

        bool operator<(const Hand& other) const;
        bool operator>(const Hand& other) const;

    //private:
        void calculateValue();
        void initRanks();
        void initSuits();
        void initBestHand();

        bool hasStraightFlush();
        bool hasFourOfAKind();
        bool hasFullHouse();
        bool hasFlush();
        bool hasStraight();
        bool hasThreeOfAKind();
        bool hasTwoPair();
        bool hasPair();
        void hasNoHand();

        std::vector<Card> mVCards;
        HandValue mBestHand;
        std::map<int,int> mRanks;
        std::map<int,int> mSuits;
    };
    
}

#endif
