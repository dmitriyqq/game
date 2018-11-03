#pragma once
#include "VoxelSpace.hpp"

class ISpaceGenerator{
    public:
    virtual void generate(ISpace &space, int width, int height, int depth) = 0;
};
