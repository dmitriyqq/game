#pragma once

#include <list>
#include <map>
#include "SparsedChunk.hpp"
#include "Voxel.hpp"

class ISpace{
public:
    virtual const Voxel& get(Vector3i pos) const = 0;
    virtual void set(Vector3i pos, const Voxel &voxel) = 0;
};

class SimpleSpace: public ISpace{
    std::map<Vector3i, Voxel> _space;

public:
    const Voxel& get(Vector3i pos) const override
    {
        std::cout<<"space"<<std::endl;
        for(auto &&voxel: _space){
            std::cout<<"voxel "<<voxel.first.x<<" "<<voxel.first.y<<std::endl;
        }
        return _space.at(pos);
    }

    void set(Vector3i pos, const Voxel &voxel) override { _space[pos] = Voxel(voxel); }
};
