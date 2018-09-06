#pragma once

#include "Vector3i.hpp"

struct Voxel
{
    enum class Type
    {
        AIR = 0,
        BLOCK = 1
    } type;

    Vector3i position;
};