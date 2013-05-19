/**-------------------------/// Card.h \\\---------------------------
 *
 * <b>Card</b>
 * @version : 1.0
 * @since : 2012 Aug 30
 *
 * @description :
 *     Interface of the Card class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO : ADD DOC
 *
 *--------------------------\\\ Card.h ///---------------------------*/


#ifndef Card_H
#define Card_H

#include <string>

namespace pcore 
{
    enum Face {JACK = 11, QUEEN = 12, KING = 13, ACE = 14};
    enum Suit {DIAMOND, HEART, CLUB, SPADE};

    const int MAX_RANK(ACE);
    const int MIN_RANK(2);
    const int MAX_SUIT(SPADE);
    const int MIN_SUIT(DIAMOND);

class Card
{
public:
    Card( int rank, int suit );
    int getRank() const;
    int getSuit() const;

    friend inline bool operator<(const Card &c1, const Card &c2) {return c1.getRank() < c2.getRank();}
    friend inline bool operator==(const Card &c1, const Card &c2) { return c1.getRank() == c2.getRank(); }

    std::string toString() const;

private:
    int mRank;
    int mSuit;
};

}

#endif
