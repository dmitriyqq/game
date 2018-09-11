#include "VoxelSpace.hpp"
#include <PerlinNoise.h>
#include <ctime>
class ISpaceGenerator{
    public:
    virtual void generate(ISpace &space, int width, int height, int depth) = 0;
};

class PerlynSpaceGenerator: public ISpaceGenerator{
    public:
    void generate(ISpace &space, int width, int height, int depth) override{
        auto logger = spdlog::get("main_logger");
        logger->info("generating space");
        siv::PerlinNoise noise(time(0));


        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                int h = noise.noise(i / (float) width , j / (float) height) * depth + depth / 4 + 10;
                logger->info("coords {} {} - height {}", i, j, h);
                for(int k = 0; k < depth; k++){
                    auto voxel = Voxel();
                    auto voxelPosition = Vector3i{i,j,k};

                    if(k > h){
                        voxel.type = Voxel::Type::AIR;
                    }else if(k < 10){
                        voxel.type = Voxel::Type::WATER;
                    }else if(k < 20){
                        voxel.type = Voxel::Type::SAND;
                    }else if(k < 30){
                        voxel.type = Voxel::Type::GRASS;
                    }else if(k < 40){
                        voxel.type = Voxel::Type::ROCK;
                    }else{
                        voxel.type = Voxel::Type::SNOW;
                    }

                    voxel.position = voxelPosition;
                    space.set(voxelPosition, voxel);
                }
            }
        }

        logger->info("space created");
    }
};