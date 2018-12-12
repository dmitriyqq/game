#pragma once

#include <Camera.hpp>
#include "../../MyGame/include/VoxelRenderingBackend.hpp"
#include <Engine/IUpdatable.hpp>
#include <Renders/OpenGL/FpsLikeCamera.hpp>
#include <Renders/OpenGL/GlfwKeyboardState.hpp>
#include <Renders/OpenGL/InputManager.hpp>
#include <Renders/OpenGL/RotatingCamera.hpp>
#include <Renders/IDrawable.hpp>

class SnakeRenderer{
    OpenGL::VoxelRenderingBackend *__renderingBackend;
    Glfw::InputManager *__iomanager;
    OpenGL::RotatingCamera __camera;
public:
    int width(){
        return __renderingBackend->width();
    }

    int height(){
        return __renderingBackend->height();
    }

    SnakeRenderer(Glfw::InputManager *&outManager): __camera(25, 0, 25, 70){
        // __renderingBackend = new OpenGL::VoxelRenderingBackend(&__camera);
        // __iomanager = new Glfw::InputManager(__renderingBackend->getWindow());
        outManager = __iomanager;
        // __iomanager->addSubscriber(&__camera);
    }

    void display(const std::vector<IDrawable *> &drawables){
        __renderingBackend->startDisplay();

        for(auto &drawable: drawables){
            // drawable->draw(__renderingBackend);
        }

        __renderingBackend->endDisplay();
    }

    void update(float delta_time){
        __camera.update(delta_time, *__iomanager);
    }
};