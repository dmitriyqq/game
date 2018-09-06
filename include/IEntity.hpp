#pragma once

#include <vector>
#include <shared_ptr>

class IEntity{

public:
    virtual void update() = 0;
    virtual void draw() = 0;
};