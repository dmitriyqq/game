#include "VoxelSpace.hpp"


class ISpaceGenerator{
    public:
    virtual void generate(ISpace &space, int width, int height, int depth) = 0;
};

class PerlynSpaceGenerator: public ISpaceGenerator{
    public:
    void generate(ISpace &space, int width, int height, int depth) override{
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                for(int k = 0; k < depth; k++){
                    auto voxel = Voxel();
                    auto voxelPosition = Vector3i{i,j,k};
                    voxel.type = Voxel::Type::BLOCK;
                    voxel.position = voxelPosition;
                    space.set(voxelPosition, voxel);
                }
            }
        }
    }
};