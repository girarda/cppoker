#include "gtest/gtest.h"
#include "src/core/Player.h"
#include "src/interface/ConsolePlayer.h"
#include <string>

class ConsolePlayerTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            p = new pinterface::ConsolePlayer("Alex", 500);
        }
        virtual void TearDown()
        {
            delete p;
        }

        pcore::IPlayer *p;
};

TEST_F(ConsolePlayerTest, Constructor)
{
    ASSERT_EQ(p->getName(), "Alex");
    ASSERT_EQ(p->getMoney(), 500);
}

TEST_F(ConsolePlayerTest, setMoney)
{
    p->setMoney(0);
    ASSERT_EQ(p->getMoney(), 0);
}

TEST_F(ConsolePlayerTest, setName)
{
    p->setName("Alexandre");
    ASSERT_EQ(p->getName(), "Alexandre");
}

//TODO other tests
