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
#define DECK_H

#include "core/Card.h"
#include <vector>

namespace pcore
{

    const int DECK_SIZE(52);

    class Deck
    {
    public:
        Deck();
        void burn();
        void init();
        void shuffle();
        const Card& draw();

        int getCount() const;
    private:
        std::vector<Card> mVCards;
        int mPosition;
    };
}

#endif
