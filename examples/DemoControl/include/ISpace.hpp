#pragma once

#include "Voxel.hpp"

class ISpace{
public:
    virtual const Voxel& get(const Vector3i &pos) const = 0;
    virtual void set(Vector3i pos, const Voxel &voxel) = 0;
};