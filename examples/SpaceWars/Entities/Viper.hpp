#pragma once

#include <Renders/OpenGL/Model.hpp>
#include <Renders/OpenGL/MeshWithBoundingBox.hpp>

#include "DynamicEntity.hpp"

#include <reactphysics3d.h>

class Player;

class Viper : public DynamicEntity {
        Player *__player = nullptr;
        float __speed = 1.0f;
    public:
        Viper(
            OpenGL::PositionShaderProgram *program,
            OpenGL::IBoundingBoxDrawable *drawable,
            glm::vec3 scale):
        DynamicEntity(program, drawable, scale)
        {
        }
 
        void draw() const override {
            DynamicEntity::draw();
        }

        void update(float delta_time) override {
            // __theta += __speed * delta_time;
            __body->applyForceToCenterOfMass(rp3d::Vector3(-0.01f, 0, 0));
        }
};
