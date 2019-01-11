#pragma once

#include "Player.hpp"

class ComputerPlayer: public Player {
public:
    ComputerPlayer(const std::string &name): Player(name) {}
};
