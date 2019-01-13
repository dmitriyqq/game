#pragma once

#include <Renders/OpenGL/Model.hpp>
#include <Renders/OpenGL/MeshWithBoundingBox.hpp>

#include "DynamicEntity.hpp"
#include "Unit.hpp"

#include <reactphysics3d.h>

class Player;

class Viper : public Unit {
        Player *__player = nullptr;
        float __speed = 1.0f;
    public:
        Viper(OpenGL::PositionShaderProgram *program, OpenGL::IBoundingBoxDrawable *drawable, glm::vec3 scale, const std::string & name):
        Unit(program, drawable, scale, name)
        {
        }
 
        void update(float delta_time) override {
            // __theta += __speed * delta_time;
            __body->applyForceToCenterOfMass(rp3d::Vector3(-0.1f, 0, 0));
        }
};
