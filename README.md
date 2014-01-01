cppoker
=========

This is a multiplayer poker game implemented in C++ using Boost.Asio for asynchronous communication. The game can be played using a Telnet client. The AI uses pre-simulated pre-flop simulations and online post-flop simulations to evaluate their probabilities of having a winning hand. They also use game context and opponents modeling to be able to learn when their opponents are bluffing.

## Requires
+ Boost
+ make
+ cmake

## How to compile
* `make gen-cmake` to produce the necessary cmake
* `make check` to compile and run unit tests