#pragma once

#include "StaticEntity.hpp"

class GlobeBody: public StaticEntity {
    float __radius = 1.0f;
    float __theta = 1.0f;
    float __speed = 1.0f;

public:
    float getRadius() const {
        return __radius;
    }

    float getTheta() const {
        return __theta;
    }

    float getSpeed() const {
        return __speed;
    }

    GlobeBody(OpenGL::Model *model,
         OpenGL::PositionShaderProgram *program,
         rp3d::DynamicsWorld *world,
         glm::vec3 position,
         float radius):
            StaticEntity(program, model,
                         glm::vec3(radius, radius, radius)),
            __radius(radius)
    {
        addToWorld(world, position);
    }

     void setBoundingBox() override {
        auto shape = new rp3d::SphereShape(__radius);
       rp3d::decimal mass = rp3d::decimal(4.0);
        __proxyShape = __body->addCollisionShape(shape, rp3d::Transform::identity(), mass);
    }

    void update(float delta_time) {
        __theta += __speed * delta_time;
    }

    void draw() const override {
        StaticEntity::draw();
    }
};