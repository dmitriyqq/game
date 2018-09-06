#pragma once

#include <list>
#include <map>
#include "SparsedChunk.hpp"
#include "Voxel.hpp"

class ISpace{
    Voxel& get(int x, int y, int z) = 0;
};

class SimpleSpace{
    std::map<Vector3i, Voxel> _space;

public:
    Voxel& get(Vector3i pos) const { return _space[pos]; }

    void set(Vector3i pos, const Voxel &voxel) const { _space[pos] = Voxel(voxel); }
};

// class VoxelSpace: public ISpace{
//     std::list < std::shared_ptr<IChunk> > visible_chunks;
// public:
    
// }