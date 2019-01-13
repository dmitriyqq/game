#pragma once

#include <string>

class IPlayer {
public:
    virtual const std::string& getName() const = 0;
};
