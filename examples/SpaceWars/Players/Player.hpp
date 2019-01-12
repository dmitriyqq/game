#pragma once

#include <string>

class Player {
    class Entity;
    Entity * __selectedObject = nullptr;

    std::string __name;

public:
    Player(const std::string &name): __name(name){}

    const std::string& getName() const { return __name; }

    void selectAllEntities(float x1, float y1, float x2, float y2) {}
};
