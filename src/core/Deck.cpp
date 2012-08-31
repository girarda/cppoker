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
    void Deck::init()
    {
        mVCards.clear();
    
        for ( int rank = MIN_RANK; rank <= MAX_RANK; rank++ )
        {
            for ( int suit = MIN_SUIT; suit <= MAX_SUIT; ++suit )
            {
                mVCards.push_back(Card(rank, suit));
            }
        }
    }

    Deck::Deck() : mVCards()
    {
        Deck::init();
    }

    Deck::~Deck()
    {
    }

    void Deck::burn()
    {
        assert(mVCards.size() > 0);
        mVCards.pop_back();
    }

    Card *Deck::drawCard()
    {
        Card *drewCard = new Card(mVCards.back());
        Deck::burn();
        return drewCard;
    }
    
    int Deck::getSize() const
    {
        return mVCards.size();
    }

    void Deck::shuffle()
    {
        std::random_shuffle (mVCards.begin(), mVCards.end());
    }

    
}
