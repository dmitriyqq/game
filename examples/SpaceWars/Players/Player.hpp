#pragma once

#include "../Entities/Planet.hpp"
#include "../StarsFactory.hpp"
#include "../Entities/Entity.hpp"

class Player {
    Entity * __selectedObject = nullptr;

    std::string __name;

public:
    Player(const std::string &name): __name(name){}

    const std::string& getName() const { return __name; }

};
