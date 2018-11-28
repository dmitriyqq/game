#pragma once

#include <list>
#include <map>
#include <Renders/IDrawable.hpp>
#include <VoxelRenderingBackend.hpp>
#include <Renders/OpenGL/ICamera.hpp>
#include "Voxel.hpp"
#include "ISpace.hpp"
#include "IVoxelRenderingBackend.hpp"

class VoxelSpace: public ISpace{
    std::map<Vector3i, Voxel> __space;
    IVoxelRenderingBackend *__backend = nullptr;
public:
    VoxelSpace(){
//        __backend = new OpenGL::VoxelRenderingBackend();
    };

    void useBackend(IVoxelRenderingBackend *backend){
        __backend = backend;
    }

    const Voxel& get(const Vector3i &pos) const override
    {
        if(__space.find(pos) == __space.end()){
            return Voxel::NullVoxel();
        }

        return __space.at(pos);
    }

    void set(Vector3i pos, const Voxel &voxel) override
    {
        __space[pos] = Voxel(voxel);
    }

    void draw(OpenGL::ICamera *camera) const {
        __backend->useCamera(camera);
        for(auto voxel: __space){
            auto pos = voxel.first;
            __backend->display(voxel.second, pos.x, pos.y, pos.z);
        }
    }

};
