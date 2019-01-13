#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/IBoundingBoxDrawable.hpp>
#include <Renders/OpenGL/Utils.hpp>

#include <vector>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <reactphysics3d.h>

#include "Entity.hpp"

class DrawableEntity: public Entity {
protected:
    OpenGL::IBoundingBoxDrawable *__drawable = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;


public:
    DrawableEntity(
        OpenGL::PositionShaderProgram *program,
        OpenGL::IBoundingBoxDrawable *drawable):  __drawable(drawable), __program(program)
    {}

    void draw() const override {
        __drawable->draw();
    }
};
