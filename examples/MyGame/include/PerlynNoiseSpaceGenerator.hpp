#pragma once

#include "./ISpaceGenerator.hpp"
#include <PerlinNoise.h>
#include <ctime>

class PerlynSpaceGenerator: public ISpaceGenerator{
public:
    void generate(ISpace &space, int width, int height, int depth) override{
        siv::PerlinNoise noise((uint32_t)time(nullptr));
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                int h = 12; //(int) (noise.noise(i/(float)width, j/(float)height)*depth+depth/4.0);
//                std::cout <<i <<" "  << j << " - " << h << " / "<< noise.noise(i / (float) width , j / (float) height) * depth <<std::endl;
                for(int k = 0; k < depth; k++){
                    auto voxel = Voxel();
                    auto voxelPosition = Vector3i{i,k,j};

                    if(k > h){
                        voxel.type = Voxel::Type::AIR;
                    }else if(k < 3){
                        voxel.type = Voxel::Type::WATER;
                    }else if(k < 5){
                        voxel.type = Voxel::Type::SAND;
                    }else if(k < 7){
                        voxel.type = Voxel::Type::GRASS;
                    }else if(k < 9){
                        voxel.type = Voxel::Type::ROCK;
                    }else{
                        voxel.type = Voxel::Type::SNOW;
                    }

                    space.set(voxelPosition, voxel);
                }
            }
        }
    }
};