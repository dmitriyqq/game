#pragma once

#include "DynamicEntity.hpp"

class Unit: public DynamicEntity {
    std::string __name;
public:
    Unit(OpenGL::PositionShaderProgram *program, OpenGL::IBoundingBoxDrawable *drawable, glm::vec3 scale, const std::string & name):
     DynamicEntity(program, drawable, scale), __name(name) {

    }
};
