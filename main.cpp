#include <iostream>
#include <ctime>
#include <exception>
#include "network/Server.h"
#include "network/OnlineRoom.h"
#include "pokerGame/GameEngine.h"

#include "boost/thread/thread.hpp"

void initRandom();

int main(int argc, char** argv) {

//    initRandom();

//    pokerGame::GameEngine* room = new pokerGame::GameEngine();
//    network::Server ts((network::OnlineRoom*) room);
//    ts.initService(); //function does not return.
//    while (true)
//    {
//        boost::this_thread::sleep(boost::posix_time::millisec(1000));
//        if (room->getNumberOfPlayers() == 2)
//            room->start();
//    }

    return 0;
}

/* This function is critical for RNG */
void initRandom()
{
    std::srand(time(nullptr));
}

