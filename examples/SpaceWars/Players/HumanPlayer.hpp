#pragma once

#include "Player.hpp"

class HumanPlayer: public Player {
public:
    HumanPlayer(const std::string &name): Player(name) {}
};

