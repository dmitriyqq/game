#pragma once

#include <Model/Vector3.hpp>

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

    static const Voxel& NullVoxel(){
        static Voxel voxel = {
                .type = Type::AIR
        };
        return voxel;
    }
};