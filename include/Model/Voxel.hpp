#pragma once

#include "Vector3i.hpp"

struct Voxel
{
    enum class Type
    {
        AIR = 0,
        WATER = 1,
        SAND = 2,
        GRASS = 3,
        ROCK = 4,
        SNOW = 5

    } type;

    Vector3i position;

    static const Voxel& NullVoxel(){
        static Voxel voxel = {
                .type = Type::AIR,
                .position = {0,0,0}
        };
    }
};