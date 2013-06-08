#include "core/Hand.h"
#include <algorithm>

namespace pcore
{
    Hand::Hand(): size(0) ,cards(), bestHand(NO_HAND_VALUE)
    {}

    int Hand::getSize() const
    {
        return cards.size();
    }

    void Hand::addCard(const pcore::Card &aCard)
    {
        cards.push_back(aCard);
        calculateBestHand();
    }

    HandValue Hand::getHandValue() const
    {
        return bestHand;
    }

    void Hand::calculateBestHand()
    {
        std::sort(cards.begin(), cards.end());
        std::reverse(cards.begin(), cards.end());
        bestHand = getStraightFlushValue();
        if (bestHand.type == NO_HAND)
            bestHand = getFullHouseValue();
        if (bestHand.type == NO_HAND)
            bestHand = getFlushValue();
        if (bestHand.type == NO_HAND)
            bestHand = getStraightValue();
        if (bestHand.type == NO_HAND)
            bestHand = getThreeOfAKindValue();
        if (bestHand.type == NO_HAND)
            bestHand = getTwoPairsValue();
        if (bestHand.type == NO_HAND)
            bestHand = getPairValue();
        if (bestHand.type == NO_HAND)
            bestHand = getHighCardValue(); 
    }

    HandValue Hand::getStraightFlushValue() const
    {
        HandValue straightFlushValue = {NO_HAND, {0,0,0,0,0}};

        if (getSize() < 5)
            return straightFlushValue;

        for (int i =0; i < getSize() - 4; i++)
        {
            if (cards[i].getRank() == cards[i+1].getRank() + 1 &&
                    cards[i].getRank() == cards[i+2].getRank() + 2 &&
                    cards[i].getRank() == cards[i+3].getRank() + 3 &&
                    cards[i].getRank() == cards[i+4].getRank() + 4 &&
                    cards[i].isSameSuit(cards[i+1])&&
                    cards[i].isSameSuit(cards[i+2])&&
                    cards[i].isSameSuit(cards[i+3])&&
                    cards[i].isSameSuit(cards[i+4]))
            {
                straightFlushValue.type = STRAIGHT_FLUSH;
                straightFlushValue.ranks[0] = cards[i].getRank();
                break;
            }
        }
        return straightFlushValue;
    }

    HandValue Hand::getFullHouseValue() const
    {
        HandValue fullHouseValue = {NO_HAND, {0,0,0,0,0}};
        if (getSize() < 4)
            return fullHouseValue;
        for (int i = 0; i < getSize() -3; i++)
        {
            if (cards[i] == cards[i+1] && cards[i] == cards[i+2] && cards[i] == cards[i+3])
            {
                fullHouseValue.type = FULL_HOUSE;
                fullHouseValue.ranks[0] = cards[i].getRank();
                break;
            }
        }
        if (fullHouseValue.type == FULL_HOUSE)
        {
            for (int i = 0; i < getSize(); i++)
            {
                if (cards[i].getRank() != fullHouseValue.ranks[0])
                {
                    fullHouseValue.ranks[1] = cards[i].getRank();
                    break;
                }
            }
        }
        return fullHouseValue;
    }

    HandValue Hand::getFlushValue() const
    {
        HandValue flushValue = {NO_HAND, {0,0,0,0,0}};

        if (getSize() < 5)
            return flushValue;
        int nbSuits[4] = {0};

        for (int i = 0; i < getSize(); i++)
        {
            nbSuits[cards[i].getSuit()]++;
        }
        for (int i = MIN_SUIT; i <= MAX_SUIT; i++)
        {
            if (nbSuits[i] >=5)
            {
                flushValue.type = FLUSH;
                int j = 0;
                for (int k = 0; k < getSize(); k++)
                {
                    if (cards[k].getSuit() == i)
                    { 
                        flushValue.ranks[j] = cards[k].getRank();
                        j++;
                        if (j == 5)
                        {
                            return flushValue;
                        }
                    }
                }
            }
        }
        return flushValue;
    }

    HandValue Hand::getStraightValue() const
    {
        HandValue straightValue = {NO_HAND, {0,0,0,0,0}};

        if (getSize() < 5)
            return straightValue;

        for (int i =0; i < getSize() - 4; i++)
        {
            if (cards[i].getRank() == cards[i+1].getRank() + 1 &&
                    cards[i].getRank() == cards[i+2].getRank() + 2 &&
                    cards[i].getRank() == cards[i+3].getRank() + 3 &&
                    cards[i].getRank() == cards[i+4].getRank() + 4)
            {
                straightValue.type = STRAIGHT;
                straightValue.ranks[0] = cards[i].getRank();
                break;
            }
        }
        return straightValue;
    }

    HandValue Hand::getThreeOfAKindValue() const
    {
        HandValue threeOfAKindHandValue = {NO_HAND, {0,0,0,0,0}};
        for (int i = 0; i < getSize() -2; i++)
        {
            if (cards[i] == cards[i+1] && cards[i] == cards[i+2])
            {
                threeOfAKindHandValue.type = THREE_OF_A_KIND;
                threeOfAKindHandValue.ranks[0] = cards[i].getRank();
                break;
            }
        }
        if (threeOfAKindHandValue.type == THREE_OF_A_KIND)
        {
            int j = 0;
            for (int i = 0; i < std::min(getSize(), 2); i++)
            {
                if (cards[i].getRank() != threeOfAKindHandValue.ranks[0])
                {
                    j++;
                    threeOfAKindHandValue.ranks[j] = cards[i].getRank();
                    if (j == 2)
                        break;
                }
            }
        }
        return threeOfAKindHandValue;
    }

    HandValue Hand::getTwoPairsValue() const
    {
        std::vector<Card> cardsCopy(cards);
        HandValue twoPairsHandValue = {NO_HAND, {0, 0, 0, 0, 0}};
        int pairs[2];
        int nbPairs = 0;
        for(int i = 0; i < std::min(HAND_SIZE, getSize()) -1; i++)
        {
            if (cardsCopy[i] == cardsCopy[i+1])
            {
                pairs[nbPairs] = cardsCopy[i].getRank();
                nbPairs++;
                if (nbPairs == 2)
                    break;
            }
        }
        if (nbPairs != 2)
            return twoPairsHandValue;
        else
        {
            twoPairsHandValue.type = TWO_PAIRS;
            for (int i = 0; i < 2; i++)
                twoPairsHandValue.ranks[i] = pairs[i];
            for (int i = 0; i < getSize(); i++)
            {
                if (cardsCopy[i].getRank() != pairs[0] && cardsCopy[i].getRank() != pairs[1])
                {
                    twoPairsHandValue.ranks[2] = cardsCopy[i].getRank(); 
                    break;
                }
            }
            return twoPairsHandValue;
        }
    }

    HandValue Hand::getPairValue() const
    {
        std::vector<Card> cardsCopy(cards);
        HandValue pairHandValue = {NO_HAND, {0, 0, 0, 0, 0}};
        for(int i = 0; i < std::min(HAND_SIZE, getSize()) -1; i++)
        {
            if (cardsCopy[i] == cardsCopy[i+1])
            {
                pairHandValue.type = PAIR;
                pairHandValue.ranks[0] = cardsCopy[i].getRank();
                cardsCopy.erase(cardsCopy.begin()+i+1);
                cardsCopy.erase(cardsCopy.begin()+i);
                break;
            }
        }
        for (int i = 0; i < std::min(4, (int)cardsCopy.size()); i++)
        {
            pairHandValue.ranks[i+1] = cardsCopy[i].getRank();
        }
        return pairHandValue;
    }

    HandValue Hand::getHighCardValue() const
    {
        HandValue highCardHandValue = {HIGH_CARD, {0, 0, 0, 0, 0}};
        for(int i = 0; i < std::min(HAND_SIZE, getSize()); i++)
        {
            highCardHandValue.ranks[i] = cards[i].getRank();; 
        }
        return highCardHandValue;
    }

    bool Hand::operator<(const Hand& other) const
    {
        if (bestHand.type != other.getHandValue().type)
        {
            return bestHand.type < other.getHandValue().type;
        }

        for( int i(0) ; i < pcore::HAND_SIZE ; i++ )
        {
            if (bestHand.ranks[i] != other.getHandValue().ranks[i])
            {
                return  bestHand.ranks[i] < other.getHandValue().ranks[i];
            }
        }
    }

    bool Hand::operator>(const Hand& other) const
    {
        return other < *this;
    }

    bool operator==(const HandValue &h1, const HandValue &h2) 
    {
        if (h1.type != h2.type)
            return false;
        for (int i = 0; i < HAND_SIZE; i++)
        {
            if (h1.ranks[i] != h2.ranks[i])
                return false;
        }
        return true;
    }
}
