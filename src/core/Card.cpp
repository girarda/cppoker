/**-------------------------/// Card.cpp \\\---------------------------
 *
 * <b>Card.cpp</b>
 * @version : 1.0
 * @since : 2012 Aug 30
 *
 * @description :
 *     Implementation of the Card class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO : ADD DOC
 *
 *--------------------------\\\ Card.cpp ///---------------------------*/

#include "core/Card.h"
#include <assert.h>
#include <sstream>

namespace pcore
{
    /**
     * \fn Card::Card(int rank, int suit): mRank(rank), mSuit(suit)
     */
    Card::Card(int rank, int suit): mRank(rank), mSuit(suit)
    {
        assert(mRank <= pcore::MAX_RANK && mRank >= pcore::MIN_RANK);
        assert(mSuit <= pcore::MAX_SUIT && mSuit >= pcore::MIN_SUIT);
    }
    
    /**
     * \fn int Card::getRank() const
     * 
     * \return rank of the card
     */
    int Card::getRank() const
    {
        return mRank;
    } 

    /**
     * \fn int Card::getSuit() const
     *
     * \return suit of the card
     */
    int Card::getSuit() const
    {
        return mSuit;
    }

    bool Card::isSameSuit(const Card &other) const
    {
        return mSuit == other.mSuit;
    }

    /**
     * \fn std::string Card::toString() const
     *
     * \return string representing the card
     */
    std::string Card::toString() const
    {
        std::stringstream ss;
        ss << mRank;
        std::string retval;
        if (mRank < 11)
            retval = ss.str();
        else if (mRank == 11)
            retval = "J";
        else if (mRank == 12)
            retval = "Q";
        else if (mRank == 13)
            retval = "K";
        else if (mRank == 14)
            retval = "A";
        
        switch(mSuit)
        {
            case (DIAMOND):
                retval += "D";
                break;
            case (HEART):
                retval += "H";
                break;
            case (CLUB):
                retval += "C";
                break;
            case (SPADE):
                retval += "S";
                break;
            default:
                retval+="Error";
        }

        return retval;
    }
}
