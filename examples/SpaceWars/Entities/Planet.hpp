#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/ModelPosition.hpp>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <reactphysics3d.h>

#include "GlobeBody.hpp"
#include "Renders/OpenGL/ArcBallPositionProvider.hpp"

class PlanetsFactory;

class Planet : public ArcBallPositionProvider, public GlobeBody {
    friend class PlanetsFactory;

    float __orbitRadius;
    float __speed = 0.001f;
    float __theta = 0.0f;

    void updatePosition() {
        auto vec = ArcBallPositionProvider::getPostionVector();
        GlobeBody::setPosition(vec.x, vec.y, vec.z);
        GlobeBody::setRotation(__theta);
    }

    public:
    Planet(OpenGL::Model *model, OpenGL::PositionShaderProgram *program, rp3d::DynamicsWorld *world,
           glm::vec3 position, float radius, float orbitRadius, float a, float b) :
            GlobeBody(model, program, world, position, radius),
            __orbitRadius(orbitRadius),
            __speed(b),
            ArcBallPositionProvider(position, orbitRadius, 10.0f * a, 0.0f)
    {
    }

    void update(float delta_time) {
        __phi += __speed * delta_time;
        __theta += 2 * __speed * delta_time;
        if (__phi >= 2 * 3.1451f) {
            __phi = 0.0f;
        }

        if (__theta >= 2 * 3.1451f) {
            __theta = 0.0f;
        }
        updatePosition();
    }

    Type getType() override {
        return Entity::Type::PLANET;
    }

    const char* getName() override {
        return "Planet";
    }

};
