#pragma once

#include "StaticEntity.hpp"

class GlobeBody: public StaticEntity {
    float __radius = 1.0f;
    float __theta = 1.0f;
    float __speed = 1.0f;

public:
    GlobeBody(OpenGL::Model *model,
         OpenGL::PositionShaderProgram *program,
         rp3d::DynamicsWorld *world,
         glm::vec3 position,
         float radius):
            StaticEntity(program, model,
                         glm::vec3(radius*2.0f, radius*2.0f, radius*2.0f)),
            __radius(radius)
    {
        addToWorld(world, position);
    }

    void update(float delta_time) {
        __theta += __speed * delta_time;
    }

    void draw() const override {
        StaticEntity::draw();
    }
};