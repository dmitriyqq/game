#pragma once

#include <list>
#include <map>
#include <spdlog/spdlog.h>
#include "SparsedChunk.hpp"
#include "Voxel.hpp"

class ISpace{
public:
    virtual const Voxel& get(const Vector3i &pos) const = 0;
    virtual void set(Vector3i pos, const Voxel &voxel) = 0;
};

class SimpleSpace: public ISpace{
    std::map<Vector3i, Voxel> _space;

public:
    SimpleSpace() {

    }

    const Voxel& get(const Vector3i &pos) const override
    {
        if(_space.find(pos) == _space.end()){
            return Voxel::NullVoxel();
        }
        return _space.at(pos);
    }

    void set(Vector3i pos, const Voxel &voxel) override
    {
        _space[pos] = Voxel(voxel);

    }
};
