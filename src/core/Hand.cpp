/**-------------------------/// Hand.cpp \\\---------------------------
 *
 * <b>Hand.cpp</b>
 * @version : 1.0
 * @since : 2012 Aug 31
 *
 * @description :
 *     Implementation of the Hand class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO :
 *
 *--------------------------\\\ Hand.cpp ///---------------------------*/

#include "Hand.h"
#include <cmath>
#include <assert.h>
#include <algorithm>

namespace pcore
{
    /**
     * \fn Hand::Hand()
     */
    Hand::Hand(): mVCards(), mRanks(), mSuits(), mBestHand()
    {
    }

    /**
     * \fn void Hand::addCard(const Card &newCard)
     */
    void Hand::addCard(const Card &newCard)
    {
        assert(mVCards.size() < HAND_MAX_CARDS);
        mVCards.push_back(newCard);
        calculateValue();
    }

    /**
     * \fn void Hand::empty()
     */
    void Hand::empty()
    {
        mVCards.clear();
        calculateValue();
    }

    /**
     * \fn size_t Hand::getCount() const
     *
     * \return the number of cards in the hand
     */
    size_t Hand::getCount() const
    {
        return mVCards.size();
    }

    /**
     * \fn bool Hand::operator<(const Hand& other) const
     *
     * \param[in] the hand to compare
     *
     * \return true if the hand is smaller, else, false
     */
    bool Hand::operator<(const Hand& other) const
    {
        if (mBestHand.type != other.getValue().type)
        {
            return mBestHand.type < other.getValue().type;
        }

        for( int i(0) ; i < pcore::HAND_SIZE ; i++ )
        {
            if (mBestHand.ranks[i] != other.getValue().ranks[i])
            {
                return  mBestHand.ranks[i] != other.getValue().ranks[i];
            }
        }
    }

    /**
     * \fn bool Hand::hasStraightFlush()
     *
     * \return true if the hand is a straight flush
     */
    bool Hand::hasStraightFlush()
    {
        //TODO
        return false;
    }

    /**
     * \fn bool Hand::hasFourOfAKind()
     *
     * \return true if the hand is a four of a kind
     */
    bool Hand::hasFourOfAKind()
    {
        //TODO
        return false;
    }
    
    /**
     * \fn bool Hand::hasFullHouse()
     *
     * \return true if the hand is a full house
     */
    bool Hand::hasFullHouse()
    {
        //TODO
        return false;
    }

    /**
     * \fn bool Hand::hasFlush()
     *
     * \return true if the hand is a flush
     */
    bool Hand::hasFlush()
    {
        //TODO
        return false;
    }

    /**
     * \fn bool Hand::hasStraight
     *
     * \return true if the hand is a straight
     */
    bool Hand::hasStraight()
    {
        //TODO
        return false;
    }

    /**
     * \fn bool Hand::hasThreeOfAKind()
     *
     * \return true if the hand is a three of a kind
     */
    bool Hand::hasThreeOfAKind()
    {
        //TODO
        return false;
    }

    /**
     * \fn bool Hand::hasTwoPair()
     *
     * \return true if the hand has two pairs
     */
    bool Hand::hasTwoPair()
    {
        //TODO
        return false;
    }

    /**
     * \fn bool Hand::hasPair()
     *
     * \return true if the hand has a pair
     */
    bool Hand::hasPair()
    {
        bool pair(false);
        int highestPair(0);
        for ( int rank = MIN_RANK; rank <= MAX_RANK ; rank++ )
        {
            if(mRanks[rank] == 2)
            {
                pair = true;
                highestPair = rank;
            }
        }
        if(pair)
        {
            mBestHand.type = PAIR;
            mBestHand.ranks[0] = highestPair;
            int i = 1;
            for( int rank(MAX_RANK) ; rank >= MIN_RANK ; rank-- )
            {
                if (mRanks[rank] == 1 && rank != highestPair)
                {
                    assert(i <= HAND_SIZE);
                    mBestHand.ranks[i] = rank;
                    i++;
                }
            } 
        }
        return pair;
    }

    void Hand::hasNoHand()
    {
        mBestHand.type = NO_HAND;
        int i(0);
        for ( int rank = MAX_RANK; rank >= MIN_RANK; --rank )
        {
            if(mRanks[rank] == 1 && i < HAND_SIZE)
            {
                mBestHand.ranks[i] = rank;
                i++;
            }
        }
    }

    void Hand::initRanks()
    {
        mRanks.clear();
        for(std::vector<Card>::iterator it=(mVCards.begin()) ; it!=mVCards.end() ; it++ )
        {
           mRanks[it->getRank()]++;
        }
    }
    
    void Hand::initSuits()
    {
        mSuits.clear();
        for( std::vector<Card>::iterator it=(mVCards.begin()) ; it!=mVCards.end() ; it++ )
        {
           mSuits[it->getSuit()]++;
        }
        
    }
    void Hand::calculateValue()
    {
        initRanks();
        //initSuits();
        initBestHand();
        if (!hasStraightFlush())
        {
            if (!hasFourOfAKind())
                {
                if(!hasFullHouse())
                {
                    if(!hasFlush())
                    {
                        if(!hasStraight())
                        {
                            if(!hasThreeOfAKind())
                            {
                                if(!hasTwoPair())
                                {
                                    if(!hasPair())
                                    {
                                        hasNoHand();
                                    }
                                }
                            }
                        }
                    }
                }
            }   
        }
    }

    const HandValue& Hand::getValue() const
    {
        return mBestHand;
    }

    void Hand::initBestHand()
    {
        mBestHand.type = NO_HAND;
        for( int i(0) ; i < HAND_SIZE; i++)
        {
            mBestHand.ranks[i] = 0;
        }
        
    }
    
}
