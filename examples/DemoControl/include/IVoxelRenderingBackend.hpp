#pragma once

#include "Voxel.hpp"
#include <Renders/OpenGL/ICamera.hpp>

class IVoxelRenderingBackend
{
public:

    virtual int width() = 0;

    virtual int height() = 0;

    virtual void startDisplay() = 0;

    virtual void display(const Voxel &voxel, int x, int y, int z) const = 0;

    virtual void endDisplay() = 0;

    virtual void useCamera(OpenGL::ICamera *camera) = 0;
};