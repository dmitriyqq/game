#pragma once

#include "IWindow.hpp"

class IDrawable{
public:
    virtual void draw(IWindow *window) const = 0;
};
