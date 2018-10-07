#pragma once

#include "IRenderingBackend.hpp"

class IDrawable{
public:
    virtual void draw(IRenderingBackend *backend) const = 0;
};
