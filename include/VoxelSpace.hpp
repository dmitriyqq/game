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
    const Voxel& get(const Vector3i &pos) const override
    {
        auto logger = spdlog::get("main_logger");
        logger->debug("access of voxel {}, {}, {}", pos.x, pos.y, pos.z);
        return _space.at(pos);
    }

    void set(Vector3i pos, const Voxel &voxel) override
    {
        _space[pos] = Voxel(voxel);
    }
};
