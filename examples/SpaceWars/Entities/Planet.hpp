#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/ModelPosition.hpp>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <reactphysics3d.h>

#include "GlobeBody.hpp"
#include "../ArcBallPositionProvider.hpp"

class Planet : public ArcBallPositionProvider, public GlobeBody {
    float __orbitRadius = 1.0f;
    float __speed;

    void updatePosition() {
        auto vec = ArcBallPositionProvider::getPostionVector();
        GlobeBody::setPosition(vec.x, vec.y, vec.z);
    }

    public:
    Planet(OpenGL::Model *model, OpenGL::PositionShaderProgram *program, rp3d::DynamicsWorld *world,
           glm::vec3 position, float radius, float orbitRadius) :
            GlobeBody(model, program, world, position, radius)
    {
        __orbitRadius = (rand() % 10);
        __speed = 1.0f / (rand() % 100 + 1);
        __center = position;
    }

    void update() {
        __phi += __speed;
        updatePosition();
    }

};
