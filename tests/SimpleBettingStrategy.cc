#include "gtest/gtest.h"
#include "HandMock.h"
#include "playerInterface/bot/SimpleBettingStrategy.h"
#include "pokerGame/BettingContext.h"

using ::testing::Return;

class SimpleBettingStrategy : public ::testing::Test {
protected:
    std::vector<pokerGame::Card>* hole;
    std::vector<pokerGame::Card>* sharedCards;
    playerInterface::bot::BettingStrategy* simpleBettingStrategy;
    pokerGame::BettingContext* bettingContext;

    static const float A_BET;
    static const float ZERO_BET;
    static const float BIG_BLIND;
    static const int NUMBER_OF_RAISES;
    static const int NUMBER_OF_PLAYERS;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;

    void initPreFlopPair();
    void initPreFlopSumOfPowerHigherThan16();
    void initPreFlopSumOfPowerLowerThan16();
    void initPostFlopStraight();
    void initPostFlopHighCard();
    void initPostFlopPair();

    virtual void SetUp() {
        hole = new std::vector<pokerGame::Card>();
        sharedCards = new std::vector<pokerGame::Card>();
        simpleBettingStrategy = new playerInterface::bot::SimpleBettingStrategy();
        bettingContext = new pokerGame::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);
    }
    virtual void TearDown() {
        delete hole;
        delete sharedCards;
        delete simpleBettingStrategy;
        delete bettingContext;
    }
};

const float SimpleBettingStrategy::A_BET(10);
const float SimpleBettingStrategy::ZERO_BET(0);
const float SimpleBettingStrategy::BIG_BLIND(1);
const int SimpleBettingStrategy::NUMBER_OF_RAISES(0);
const int SimpleBettingStrategy::NUMBER_OF_PLAYERS(2);
const pokerGame::BettingRoundType SimpleBettingStrategy::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);

//TEST_F(SimpleBettingStrategy, whenPreFlopIfHandValueIsAPairMakeDecisionReturnsRaise) {
//    initPreFlopPair();
//    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::RAISE, choice);
//}

//TEST_F(SimpleBettingStrategy, whenPreFlopIfHandValueIsAPairNewBetEqualsSumOfMinBetAndBigBlind) {
//    initPreFlopPair();
//    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
//}

//TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsHigherThan16MakeDecisionReturnsCall) {
//    initPreFlopSumOfPowerHigherThan16();
//    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::CALL, choice);
//}

//TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsHigherThan16NewBetIsInitialBet) {
//    initPreFlopSumOfPowerHigherThan16();
//    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET, newBet);
//}

//TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsLowerThan16MakeDecisionReturnsCall) {
//    initPreFlopSumOfPowerLowerThan16();
//    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::FOLD, choice);
//}

//TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsLowerThan16NewBetIsZero) {
//    initPreFlopSumOfPowerLowerThan16();
//    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(0, newBet);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHigherOrEqualsToStraightMakeDecisionReturnsRaise) {
//    initPostFlopStraight();
//    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::RAISE, choice);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHigherOrEqualsToStraightNewBetEqualsSumOfMinBetAndBigBlind) {
//    initPostFlopStraight();
//    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenFold) {
//    initPostFlopHighCard();
//    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::FOLD, choice);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenNewBetIsZero) {
//    initPostFlopHighCard();
//    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(0, newBet);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsZeroThenCall) {
//    initPostFlopHighCard();
//    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, ZERO_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::CALL, choice);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsZeroThenNewBetIsInitialBet) {
//    initPostFlopHighCard();
//    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, ZERO_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(ZERO_BET, newBet);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsBetterThanHighCardButLessThanStraifhtThenCall) {
//    initPostFlopPair();
//    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::CALL, choice);
//}

//TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsBetterThanHighCardButLessThanStraifhtThenNewBetIsInitialBet) {
//    initPostFlopPair();
//    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET, newBet);
//}

void SimpleBettingStrategy::initPreFlopPair() {
    pokerGame::Card c1(pokerGame::ACE, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::ACE, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingStrategy::initPreFlopSumOfPowerHigherThan16() {
    pokerGame::Card c1(pokerGame::KING, pokerGame::SPADE);
    pokerGame::Card c2(pokerGame::QUEEN, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingStrategy::initPreFlopSumOfPowerLowerThan16() {
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingStrategy::initPostFlopStraight() {
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    pokerGame::Card c3(4, pokerGame::HEART);
    pokerGame::Card c4(5, pokerGame::HEART);
    pokerGame::Card c5(6, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
    sharedCards->push_back(c4);
    sharedCards->push_back(c5);
}

void SimpleBettingStrategy::initPostFlopHighCard() {
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    pokerGame::Card c3(4, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
}

void SimpleBettingStrategy::initPostFlopPair() {
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(2, pokerGame::HEART);
    pokerGame::Card c3(4, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
}
