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

    void Player::setName(std::string name)
    {
        mPlayer->setName(name);
    }

    /**
     * \fn void Player::seeDealer(std::string dealer)
     *
     * \brief Announce the dealer 
     */
    void Player::seeDealer(std::string dealer)
    {
        mPlayer->seeDealer(dealer);
    }

    /**
     * \fn void Player::seeBigBlind(std::string player, Money bigblind)
     *
     * \brief Announce whoe the big blind is and its value.
     */
    void Player::seeBigBlind(std::string player, Money bigBlind)
    {
        mPlayer->seeBigBlind(player, bigBlind);
    }

    /**
     * \fn void Player::seeSmallBlind(std::string player, Money smallblind)
     *
     * \brief Announce who the small blind is and its value.
     */
    void Player::seeSmallBlind(std::string player, Money smallBlind)
    {
        mPlayer->seeSmallBlind(player, smallBlind);
    }

    /**
     * \fn void Player::seeWinner(std::string winner)
     *
     * \brief Announce the winner
     */
    void Player::seeWinner(std::string winner)
    {
        mPlayer->seeWinner(winner);
    }

    /**
     * \fn void Player::seeOpponentCards(std::string opponent, const Hand& money)
     *
     * \brief Announce the opponent's cards
     */
    void Player::seeOpponentCards(std::string opponent, const Hand& hand)
    {
        mPlayer->seeOpponentCards(opponent, hand);
    }

    /**
     * \fn void Player::seeOpponentMoney(std::string opponent, Money money)
     *
     * \brief Announce the opponent's money
     */
    void Player::seeOpponentMoney(std::string opponent, Money money)
    {
        mPlayer->seeOpponentMoney(opponent, money);
    }
}
