#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/ModelPosition.hpp>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <reactphysics3d.h>

#include "../ArcBallPositionProvider.hpp"
#include "Star.hpp"

class Planet : public ArcBallPositionProvider, public Star {
    float __orbitRadius = 1.0f;
    float __speed;

    void updatePosition() {
        auto vec = ArcBallPositionProvider::getPostionVector();
        auto transform = rp3d::Transform(rp3d::Vector3(vec.x, vec.y, vec.z), rp3d::Quaternion());
        __body->setTransform(transform);
        ModelPosition::setPosition(vec.x, vec.y, vec.z);
    }

    public:
    Planet(OpenGL::Model *model,
            OpenGL::PositionShaderProgram *program,
            rp3d::RigidBody *body,
            glm::vec3 position,
            float radius,
            float orbitRadius):
        Star(model, program, body, position, radius)
    {
        __orbitRadius = (rand() % 10);
        __speed = 1.0f / (rand() % 100 + 1);
        __center = position;
    }

    // void draw() {
    //     // __texture->use();
    //     // auto model = getPositionMatrix();
    //     // model = glm::scale(model, glm::vec3(__radius, __radius, __radius));
    //     // program->setModel(model);
    //     __mesh->draw();
    // }

    void update() {
        __phi += __speed;
        updatePosition();
    }

};