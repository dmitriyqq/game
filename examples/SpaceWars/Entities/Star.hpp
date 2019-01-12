#pragma once

#include <Renders/OpenGL/Model.hpp>

#include "GlobeBody.hpp"

class StarsFactory;

class Star: public GlobeBody {
    friend class StarsFactory;
public:
    Star(OpenGL::Model *model,
    OpenGL::PositionShaderProgram *program,
    rp3d::DynamicsWorld *world,
    glm::vec3 position,
    float radius): GlobeBody(model, program, world, position, radius) {

    }

    Type getType() override {
        return Entity::Type::STAR;
    }

    const char* getName() override {
        return "Star";
    }
};

