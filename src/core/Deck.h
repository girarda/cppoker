/**-------------------------/// Deck.h \\\---------------------------
 *
 * <b>Deck.h</b>
 * @version : 1.0
 * @since : 2012 Aug 31
 *
 * @description :
 *     Interface of the Deck class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO :
 *
 *--------------------------\\\ Deck.h ///---------------------------*/

#ifndef DECK_H
#define CARD_H

#include "Card.h"
#include <vector>

namespace pcore
{

    const int DECK_SIZE_MAX(52);

    class Deck
    {
    public:
        Deck();
        ~Deck();
        void init();
        void burn();
        void shuffle();
        Card *drawCard();
        int getSize() const;
    private:
        std::vector<Card> mVCards;
    };
}

#endif
