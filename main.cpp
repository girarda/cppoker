/*
* main.cpp
*
*/

#include <iostream>
#include <ctime>
#include <exception>
#include "network/Server.h"
#include "network/OnlineRoom.h"
#include "core/GameEngine.h"

using namespace std;

void init();

int main(int argc, char** argv) {

init();

network::OnlineRoom* room = new pcore::GameEngine();
network::Server ts(room);
ts.InitialiseService(); //function does not return.

return 0;
}

/* This function is critical for RNG */
void init() {;
srand(time(nullptr));
}

