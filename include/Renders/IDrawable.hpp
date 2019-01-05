#pragma once

#include "IWindow.hpp"

class IDrawable{
public:
    virtual void draw() const = 0;
};
