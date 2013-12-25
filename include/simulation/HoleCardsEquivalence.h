#ifndef HOLECARDSEQUIVALENCE_H
#define HOLECARDSEQUIVALENCE_H

#include "pokerGame/card/Card.h"
#include <vector>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>

namespace simulation {

class HoleCardsEquivalence {
public:
    HoleCardsEquivalence(int cardValue1, int cardValue2);

    virtual int getNumber1() const;
    virtual int getNumber2() const;

    virtual std::vector<pokerGame::card::Card> equivalenceToCards() const;

    template<class Archive>
    void serialize(Archive & ar, unsigned int file_version)
    {
        ar & number1;
        ar & number2;
    }

// public for serialization
    int number1;
    int number2;
};

}

namespace boost { namespace serialization {
template<class Archive>
inline void save_construct_data(
    Archive & ar, const simulation::HoleCardsEquivalence * t, const unsigned int file_version) {
    // save data required to construct instance
    ar << t->number1;
    ar << t->number2;
}

template<class Archive>
inline void load_construct_data(Archive & ar, simulation::HoleCardsEquivalence * t, const unsigned int file_version) {
    // retrieve data from archive required to construct new instance
    int number1;
    int number2;
    ar >> number1;
    ar >> number2;
    // invoke inplace constructor to initialize instance of my_class
    ::new(t)simulation::HoleCardsEquivalence(number1, number2);
}
}
}


#endif
