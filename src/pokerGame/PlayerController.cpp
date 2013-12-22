#include "pokerGame/PlayerController.h"

namespace pokerGame {

PlayerController::PlayerController() : name("Anon") {
}

PlayerController::~PlayerController() {
}


std::string PlayerController::getName() const {
    return name;
}

void PlayerController::setName(std::string newName) {
    name = newName;
}

}
