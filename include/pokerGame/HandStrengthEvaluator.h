#ifndef HANDSTRENGTHEVALUATOR_H
#define HANDSTRENGTHEVALUATOR_H

#include<vector>
#include"Card.h"

namespace pokerGame
{

class HandStrengthEvaluator
{
public:
    HandStrengthEvaluator();
    virtual ~HandStrengthEvaluator();
    virtual double evaluate(std::vector<Card> hole, std::vector<Card> sharedCards, int numberOfPlayers);

private:
    double calculateHandStrength(int wins, int ties, int losses, int numberOfPlayers);

};

}

#endif
