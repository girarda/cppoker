#include "gtest/gtest.h"
#include "mocks/pokerGame/card/HandMock.h"
#include "playerInterface/bot/SimpleBettingStrategy.h"
#include "pokerGame/context/BettingContext.h"
#include "pokerGame/OpponentModel.h"

using ::testing::Return;

class SimpleBettingStrategy : public ::testing::Test {
protected:
    std::vector<pokerGame::card::Card>* hole;
    std::vector<pokerGame::card::Card>* sharedCards;
    playerInterface::bot::BettingStrategy* simpleBettingStrategy;
    pokerGame::context::BettingContext* bettingContext;
    std::vector<pokerGame::OpponentModel> opponentModels;

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
        hole = new std::vector<pokerGame::card::Card>();
        sharedCards = new std::vector<pokerGame::card::Card>();
        simpleBettingStrategy = new playerInterface::bot::SimpleBettingStrategy();
        bettingContext = new pokerGame::context::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);
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

TEST_F(SimpleBettingStrategy, whenPreFlopIfHandValueIsAPairMakeDecisionReturnsRaise) {
    initPreFlopPair();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::RAISE, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfHandValueIsAPairNewBetEqualsSumOfMinBetAndBigBlind) {
    initPreFlopPair();
    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsHigherThan16MakeDecisionReturnsCall) {
    initPreFlopSumOfPowerHigherThan16();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsHigherThan16NewBetIsInitialBet) {
    initPreFlopSumOfPowerHigherThan16();
    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET, newBet);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsLowerThan16MakeDecisionReturnsCall) {
    initPreFlopSumOfPowerLowerThan16();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingStrategy, whenPreFlopIfSumOfPowerOfHandIsLowerThan16NewBetIsZero) {
    initPreFlopSumOfPowerLowerThan16();
    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHigherOrEqualsToStraightMakeDecisionReturnsRaise) {
    initPostFlopStraight();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::RAISE, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHigherOrEqualsToStraightNewBetEqualsSumOfMinBetAndBigBlind) {
    initPostFlopStraight();
    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenFold) {
    initPostFlopHighCard();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenNewBetIsZero) {
    initPostFlopHighCard();
    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsZeroThenCall) {
    initPostFlopHighCard();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, ZERO_BET, BIG_BLIND, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsHighCardAndBetIsZeroThenNewBetIsInitialBet) {
    initPostFlopHighCard();
    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, ZERO_BET, BIG_BLIND, bettingContext, opponentModels).bet;
    ASSERT_EQ(ZERO_BET, newBet);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsBetterThanHighCardButLessThanStraifhtThenCall) {
    initPostFlopPair();
    pokerGame::Choice choice = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingStrategy, whenPostFlopIfHandValueIsBetterThanHighCardButLessThanStraifhtThenNewBetIsInitialBet) {
    initPostFlopPair();
    float newBet = simpleBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET, newBet);
}

void SimpleBettingStrategy::initPreFlopPair() {
    pokerGame::card::Card c1(pokerGame::card::ACE, pokerGame::card::SPADE);
    pokerGame::card::Card c2(pokerGame::card::ACE, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingStrategy::initPreFlopSumOfPowerHigherThan16() {
    pokerGame::card::Card c1(pokerGame::card::KING, pokerGame::card::SPADE);
    pokerGame::card::Card c2(pokerGame::card::QUEEN, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingStrategy::initPreFlopSumOfPowerLowerThan16() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(3, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingStrategy::initPostFlopStraight() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(3, pokerGame::card::HEART);
    pokerGame::card::Card c3(4, pokerGame::card::HEART);
    pokerGame::card::Card c4(5, pokerGame::card::HEART);
    pokerGame::card::Card c5(6, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
    sharedCards->push_back(c4);
    sharedCards->push_back(c5);
}

void SimpleBettingStrategy::initPostFlopHighCard() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(3, pokerGame::card::HEART);
    pokerGame::card::Card c3(4, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
}

void SimpleBettingStrategy::initPostFlopPair() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(2, pokerGame::card::HEART);
    pokerGame::card::Card c3(4, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
}
