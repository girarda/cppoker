/**-------------------------/// Player.cpp \\\---------------------------
 *
 * <b>Player.cpp</b>
 * @version : 1.0
 * @since : 2012 Dec 23
 *
 * @description :
 *     Implementation of the Player class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO :
 *
 *--------------------------\\\ Player.cpp ///---------------------------*/

#include "src/core/Player.h"

namespace pcore
{
    /**
     * \fn Player::Player(IPlayer playerImpl)
     */
    Player::Player(IPlayer *playerImpl): mPlayer(playerImpl), mHand(), mBigBlind(false), mSmallBlind(false), mIsPlaying(false)
    {
    }

    /**
     * \fn void Player::setMoney(Money newValue)
     *
     * \brief Set the money value
     */
    void Player::setMoney(Money newValue)
    {
        mPlayer->setMoney(newValue);
    }



    /**
     * \fn void Player::setName(std::string name)
     *
     * \brief Set the player's name
     */
    void Player::setName(std::string name)
    {
        mPlayer->setName(name);
    }

    /**
     * \fn void Player::setFold(bool fold)
     *
     * \brief Fold or unfold
     */
    void Player::setFold(bool fold)
    {
        mIsFolded = fold;
    }

    /**
     * \fn void clearPot()
     *
     * \brief Clears the player's pot
     */
    void Player::clearPot()
    {
        mPlayer->clearPot();
    }

    /**
     * \fn Money Player::getMoney() const
     *
     * \brief Return the player's amount of money.
     *
     * \return the player's amount of money
     */
    Money Player::getMoney() const
    {
        return mPlayer->getMoney();
    }

    /**
     * \fn std::string Player::getName() const
     *
     * \brief Return the player's name
     *
     * \return the player's name
     */
    std::string Player::getName() const
    {
        return mPlayer->getName();
    }

    /**
     * \fn Hand Player::getHand() const
     *
     * \brief Return te player's hand
     *
     * \return the player's hand
     */
    Hand Player::getHand() const
    {
        return mHand;
    }

    /**
     * \fn Money getPot() const
     *
     * \brief Return the player's pot
     *
     * \return the player's pot
     */
    Money Player::getPot() const
    {
        return mPlayer->getPot();
    }

    /**
     * \fn bool Player::isPlaying const
     *
     * \brief Indicates whether the playing is playing or not
     *
     * \return true if the player is playing
     */
    bool Player::isPlaying() const
    {
        return mIsPlaying;
    }

    /**
     * \fn bool Player::isFolded() const
     *
     * \brief Indicates whether the player has folded
     *
     * \return true if the player folded
     */
    bool Player::isFolded() const
    {
        return mIsFolded;
    }

    /**
     * \fn void addCard(const Card& card)
     *
     * \brief Add a new card in the player's hand
     */
    void Player::addCard(const Card& card)
    {
        mHand.addCard(card);
    }

    /**
     * \fn void Player::addToPot(Money m)
     *
     * \brief Add money to the pot
     */
    void Player::addToPot(Money m)
    {
        mPlayer->addToPot(m);
    }

    /**
     * \fn Decision Player::makeDecision()
     *
     * \brief Ask the player to make a decision
     *
     * \return the player's decision
     */
    Decision Player::makeDecision()
    {
        return mPlayer->makeDecision();
    }

    /**
     * \fn void Player::seeDealer(std::string dealer) const
     *
     * \brief Announce the dealer 
     */
    void Player::seeDealer(std::string dealer) const
    {
        mPlayer->seeDealer(dealer);
    }

    /**
     * \fn void Player::seeBigBlind(std::string player, Money bigblind) const
     *
     * \brief Announce whoe the big blind is and its value.
     */
    void Player::seeBigBlind(std::string player, Money bigBlind) const
    {
        mPlayer->seeBigBlind(player, bigBlind);
    }

    /**
     * \fn void Player::seeSmallBlind(std::string player, Money smallblind) const
     *
     * \brief Announce who the small blind is and its value.
     */
    void Player::seeSmallBlind(std::string player, Money smallBlind) const
    {
        mPlayer->seeSmallBlind(player, smallBlind);
    }

    /**
     * \fn void Player::seeWinner(std::string winner) const
     *
     * \brief Announce the winner
     */
    void Player::seeWinner(std::string winner) const
    {
        mPlayer->seeWinner(winner);
    }

    /**
     * \fn void Player::seeOpponentCards(std::string opponent, const Hand& money) const
     *
     * \brief Announce the opponent's cards
     */
    void Player::seeOpponentCards(std::string opponent, const Hand& hand) const
    {
        mPlayer->seeOpponentCards(opponent, hand);
    }

    /**
     * \fn void Player::seeOpponentMoney(std::string opponent, Money money) const
     *
     * \brief Announce the opponent's money
     */
    void Player::seeOpponentMoney(std::string opponent, Money money) const
    {
        mPlayer->seeOpponentMoney(opponent, money);
    }

    /**
     * \fn void Player::seeCards() const
     *
     * \brief Announce the player's cards
     */
    void Player::seeCards() const
    {
        mPlayer->seeCards(mHand);
    }

    /**
     * \fn void Player::seeMoney() const
     *
     * \brief Announce the player's money
     */
    void Player::seeMoney() const
    {
        mPlayer->seeMoney();
    }
}
