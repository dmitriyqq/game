#pragma once

#include <Model/Voxel.hpp>

class IRenderingBackend
{

public:

    virtual int width() = 0;

    virtual int height() = 0;

    virtual void startDisplay() = 0;

    virtual void display(const Voxel &voxel, int y, int x) const = 0;

    virtual void endDisplay() = 0;
};