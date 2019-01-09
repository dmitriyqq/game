#pragma once

#include <Renders/OpenGL/Model.hpp>
#include <Renders/OpenGL/MeshWithBoundingBox.hpp>

#include "DynamicEntity.hpp"

#include <reactphysics3d.h>

class GodPlayer;

class Asteroid : public DynamicEntity {
        GodPlayer *__player = nullptr;
        glm::vec3 __force;
    public:
        Asteroid(
            OpenGL::PositionShaderProgram *program,
            OpenGL::IBoundingBoxDrawable *drawable,
            glm::vec3 scale, glm::vec3 force):
        DynamicEntity(program, drawable, scale), __force(force)
        {
        }

        void addToWorld(rp3d::DynamicsWorld *world, glm::vec3 pos) override {
            DynamicEntity::addToWorld(world, pos);
            __body->applyForceToCenterOfMass(rp3d::Vector3(__force.x, __force.y, __force.z));
            auto x = rand()%100 / ((float)(rand()%10) + 1);
            auto y = rand()%100 / ((float)(rand()%10) + 1);
            auto z = rand()%100 / ((float)(rand()%10) + 1);
            __body->applyTorque(rp3d::Vector3(x, y, z));
        }

        void draw() const override {
            DynamicEntity::draw();
        }

        void update(float delta_time) override {
            // __theta += __speed * delta_time;
        }
};
