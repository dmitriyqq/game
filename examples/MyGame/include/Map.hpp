#pragma once

#include <VoxelSpace.hpp>
#include <ISpaceGenerator.hpp>
#include <PerlynNoiseSpaceGenerator.hpp>
#include <VoxelRenderingBackend.hpp>

class Map{
    VoxelSpace __space;
    PerlynSpaceGenerator __generator;
public:
    Map(){
        __generator.generate(__space, 128, 32, 128);
    }

    void draw(OpenGL::ICamera *camera) const {
        __space.draw(camera);
    }

    void useBackend(IVoxelRenderingBackend *backend){
        __space.useBackend(backend);
    }

    ISpace* getRawData(){
        return &__space;
    }

};