#ifndef Card_H
#define Card_H

#include <string>

namespace pokerGame
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

    bool isSameSuit(const Card &other) const;
    bool isVisible() const;

    void show();
    void hide();

    friend inline bool operator<(const Card &c1, const Card &c2) {return c1.getRank() < c2.getRank();}
    friend inline bool operator>(const Card &c1, const Card &c2) {return c2 < c1;}
    friend inline bool operator==(const Card &c1, const Card &c2) { return c1.getRank() == c2.getRank(); }

    std::string toString() const;

private:
    int rank;
    int suit;
    bool visible;
};

}

#endif
