#pragma once

#include <Renders/OpenGL/Model.hpp>
#include <Renders/OpenGL/MeshWithBoundingBox.hpp>
#include <Engine/IUpdatable.hpp>
#include <reactphysics3d.h>

#include "IEntity.hpp"

class Player;

class Star : public OpenGL::MeshWithBoundingBox, public IEntity {
        Player *__player = nullptr;

        float __radius = 1.0f;
        float __theta = 1.0f;
        float __speed = 1.0f;

        rp3d::SphereShape *__shape = nullptr;
        rp3d::ProxyShape *__proxyShape = nullptr;
    protected:
        rp3d::RigidBody *__body = nullptr;
    public:
        Star(OpenGL::Model *model,
             OpenGL::PositionShaderProgram *program,
             rp3d::RigidBody *body,
             glm::vec3 position,
             float radius):
        MeshWithBoundingBox(program, model), __body(body), __radius(radius)
        {
            rp3d::Vector3 initPosition(position.x, position.y, position.z); 
            rp3d::Quaternion initOrientation = rp3d::Quaternion::identity(); 
            rp3d::Transform transform(initPosition, initOrientation); 
            body->setTransform(transform);

            setPosition(position.x, position.y, position.z);
            setScale(2 * __radius, 2 * __radius, 2 * __radius);

            body->setType(rp3d::BodyType::STATIC);
            __shape = new rp3d::SphereShape(__radius);
            rp3d::decimal mass = rp3d::decimal(4.0); 
            __proxyShape = body->addCollisionShape(__shape, rp3d::Transform::identity(), mass); 
        }
 
        void update(float delta_time) {
            __theta += __speed * delta_time;
        }

        void draw() const override {
            MeshWithBoundingBox::draw();
        }
};
