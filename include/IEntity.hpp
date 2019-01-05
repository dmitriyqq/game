#pragma once

class IEntity{

public:
    virtual void update() = 0;
    virtual void draw() = 0;
};