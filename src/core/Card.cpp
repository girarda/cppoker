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

#include "Card.h"
#include <assert.h>

namespace pcore
{
    Card::Card(int rank, int suit): mRank(rank), mSuit(suit)
    {
        assert(mRank <= pcore::MAX_RANK && mRank >= pcore::MIN_RANK);
        assert(mSuit <= pcore::MAX_SUIT && mSuit >= pcore::MIN_SUIT);
    }
    
    int Card::getRank()
    {
        return mRank;
    } 

    int Card::getSuit()
    {
        return mSuit;
    }


}
