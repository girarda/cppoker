#include <iostream>
#include <ctime>
#include <exception>
#include "network/Server.h"
#include "network/OnlineRoom.h"
#include "pokerGame/GameEngine.h"

void initRandom();

int main(int argc, char** argv) {

    initRandom();

    network::OnlineRoom* room = new pokerGame::GameEngine();
    network::Server ts(room);
    ts.initService(); //function does not return.

    delete room;

    return 0;
}

/* This function is critical for RNG */
void initRandom()
{
    std::srand(time(nullptr));
}

