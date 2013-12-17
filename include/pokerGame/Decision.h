#ifndef DECISION_H
#define DECISION_H

namespace pokerGame
{

enum Choice {WAITING, FOLD, CHECK, CALL};

typedef struct Decision
{
    Choice choice;
    float bet;
} Decision;

}

#endif
