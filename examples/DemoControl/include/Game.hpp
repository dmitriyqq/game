#pragma once

#include <Engine/Game.hpp>
#include <Renders/OpenGL/RotatingCamera.hpp>
#include <Renders/OpenGL/InputManager.hpp>
#include <Renders/OpenGL/FpsLikeCamera.hpp>
#include <Renders/OpenGL/Window.hpp>
#include <Renders/OpenGL/DirectLight.hpp>

#include "Map.hpp"
#include "Chunk.hpp"


class Game: public Engine::IGame{
    static constexpr int RENDER_DISTANCE = 3;

    Map __map;
    IWindow * __window = nullptr;
    OpenGL::RotatingCamera *__camera;
    ChunkMesh *__meshes[RENDER_DISTANCE][RENDER_DISTANCE];
    ShaderProgram *__program;
    DirectLight __light;

    void update() override {
        __camera->update(0.05, *__window->getKeyBoardState());
        __program->setCamera(__camera, __window->getWidth(), __window->getHeight());
        auto m = __camera->getProjectionMatrix(__window->getWidth(), __window->getHeight());
        std::cout<<"update"<<std::endl;
    }

    void draw() const override {
        __window->startDisplay();
        for(int i = 0; i < RENDER_DISTANCE; i++){
            for(int j = 0; j < RENDER_DISTANCE; j++){
                auto mesh = __meshes[i][j];
                mesh->draw(__window);
            }
        }
        std::cout<<"draw"<<std::endl;
        __window->endDisplay();
        //__map.draw(__camera);
    }

public:
    Game(){
        __window = new Glfw::Window();
        __program = new ShaderProgram();
        __program->loadShaders("useLightShader.vert", "useLightShader.frag");
        // __backend = new OpenGL::VoxelRenderingBackend();
        ChunkMesh::useProgram(__program);

        //  __manager = new Glfw::InputManager(__backend->getWindow());
        // __map.useBackend(__backend);
        for(int i = 0; i < RENDER_DISTANCE; i++){
            for(int j = 0; j < RENDER_DISTANCE; j++){
                __meshes[i][j] = new ChunkMesh(__map.getRawData(), i, j);
            }
        }

        __light.uniform(__program);
        __camera = new OpenGL::RotatingCamera(0.5, 0.0, 0.5, 5);
        __camera->setPosition(glm::vec3(0.0, 0.5, 0.0));
//        __camera->setTarget();
        //  __window->getMouseInput()->addSubscriber(__camera);
        //  __backend->setupMesh(sp, 0, 0);
        //  __backend->useCamera(__camera);
    }

};