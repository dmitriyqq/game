#pragma once
#include "Renders/OpenGL/ShaderProgram.hpp"
#include <GLFW/glfw3.h>
#include <Renders/OpenGL/CubeVAO.hpp>
#include <Renders/OpenGL/CubeNormalsVAO.hpp>
#include <Renders/OpenGL/Camera.hpp>
#include <Renders/OpenGL/DirectLight.hpp>
#include "IVoxelRenderingBackend.hpp"
#include <iostream>
#include <functional>
#include "Voxel.hpp"
#include "Renders/OpenGL/ICamera.hpp"
#include <Renders/OpenGL/CubeMesh.hpp>
// #include <Chunk.hpp>

namespace OpenGL {

    class VoxelRenderingBackend : public IVoxelRenderingBackend {
        static constexpr int WIDTH = 800, HEIGHT = 800;
        ShaderProgram *myProgram;

        // ICamera *__camera;
        // ChunkMesh *__mesh = nullptr;

    // public:
//        explicit VoxelRenderingBackend(ICamera *cam = nullptr): __camera(cam) {
//            myProgram = new ShaderProgram();
//
//            CubeMesh::useProgram(myProgram);
//            ChunkMesh::useProgram(myProgram);
//        }
//
//        void useCamera(OpenGL::ICamera *camera) override {
//            __camera = camera;
//            myProgram->setCamera(__camera, WIDTH, HEIGHT);
//        }
//
//        int width() override {
//            return 50;
//        }
//
//        int height() override {
//            return 50;
//        }
//
//        void startDisplay() override {
//
//        }
//
//
//         void display(const Voxel &voxel, int x, int y, int z) const override {
            //static CubeMesh myCube;
//            mat4 model1(1);
//            switch (voxel.type){
//                case Voxel::Type::WATER:
//                    myCube.setColor(0.0, 0.0, 1.0);
//                    break;
//                case Voxel::Type::SAND:
//                    myCube.setColor(1.0, 1.0, 0.0);
//                    break;
//                case Voxel::Type::GRASS:
//                    myCube.setColor(0.0, 1.0, 0.0);
//                    break;
//                case Voxel::Type::ROCK:
//                    myCube.setColor(0.3, 0.3, 0.3);
//                    break;
//                case Voxel::Type::SNOW:
//                    myCube.setColor(0.9, 0.9, 0.9);
//                    break;
//                default:
//                    myCube.setColor(0.9, 0.9, 0.9);
//                    break;
//            }
//
//            myCube.setPosition(1.0*x, 1.0*y, 1.0*z);
//            if(voxel.type != Voxel::Type::AIR){
//                myCube.draw();
//            }
        //}

        //void endDisplay() override {
//            __mesh->draw();
//            static CubeMesh myCube;
//               // myCube.setPosition(0, 0, 0);
//                myCube.setColor(0.9, .5, 0.3);
//              //  myCube.draw();
//
       // }

        //void setupMesh(ISpace *space, int x, int y){
            // __mesh = new ChunkMesh(space, x, y);
        //}
    };

}
