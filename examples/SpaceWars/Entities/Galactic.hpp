#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d.h>

#include "Star.hpp"
#include "Planet.hpp"

class Galactic{
    static constexpr int NUM_PLANETS = 5;

    Planet *__planets[NUM_PLANETS];
    Star *__star = nullptr;

public:
    Galactic(OpenGL::Model *model,
            OpenGL::PositionShaderProgram *program,
            rp3d::DynamicsWorld &world,
            glm::vec3 position) {
                rp3d::RigidBody *sunBody = world.createRigidBody(rp3d::Transform::identity());
                __star = new Star(model, program, sunBody, position, 3.0f);
                for(int i = 0; i < NUM_PLANETS; i++) {
                    rp3d::RigidBody *body = world.createRigidBody(rp3d::Transform::identity());
                    // __planets[i] = new Planet(model, program, body, );
                }
    }
    // Galactic(glm::vec3 position): Planet() {
    //     // __sun = new Sun()
    // }
};