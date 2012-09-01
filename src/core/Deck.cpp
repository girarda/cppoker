/**-------------------------/// Deck.cpp \\\---------------------------
 *
 * <b>Deck.cpp</b>
 * @version : 1.0
 * @since : 2012 Aug 31
 *
 * @description :
 *     Implementation of the Deck class
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO : ADD DOC
 *
 *--------------------------\\\ Deck.cpp ///---------------------------*/

#include "Deck.h"
#include <assert.h>
#include <algorithm>

namespace pcore
{
    Deck::Deck() : mVCards(), mPosition(DECK_SIZE)
    {
       for( int rank(MIN_RANK) ; rank <= MAX_RANK ; rank++ )
       {
          for( int suit(MIN_SUIT) ; suit <= MAX_SUIT ; ++suit )
          {
              mVCards.push_back(Card(rank,suit));
          }
          
       }
       
    }

    void Deck::burn()
    {
        assert (mPosition > 0);
        --mPosition;
    }

    const Card& Deck::draw()
    {
        burn();
        return mVCards[mPosition];
    }
    
    void Deck::shuffle()
    {
        mPosition = DECK_SIZE;
        std::random_shuffle (mVCards.begin(), mVCards.end());
    }

    int Deck::getCount() const
    {
        return mPosition;
    }

    
}
