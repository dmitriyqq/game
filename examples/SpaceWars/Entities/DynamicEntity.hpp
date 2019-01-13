#pragma once

#include "Entity.hpp"
#include "DrawableEntity.hpp"

class DynamicEntity : public DrawableEntity {
    rp3d::BoxShape *__shape = nullptr;
    rp3d::ProxyShape *__proxyShape = nullptr;
    rp3d::DynamicsWorld *__world = nullptr;
    glm::vec3 __scale;

    void setBoundingBox() {
        auto box = __drawable->getBox();
        auto t = box.second - box.first;
        auto c = __scale;
        t.x *= c.x;
        t.y *= c.y;
        t.z *= c.z;

        const rp3d::Vector3 halfExtents(t.x, t.y, t.z);
        __shape = new rp3d::BoxShape(halfExtents);
        rp3d::decimal mass = rp3d::decimal(4.0);
        __proxyShape = __body->addCollisionShape(__shape, rp3d::Transform::identity(), mass);
    }

protected:
    rp3d::RigidBody *__body = nullptr;
public:
    DynamicEntity(
        OpenGL::PositionShaderProgram *program,
        OpenGL::IBoundingBoxDrawable *drawable,
        glm::vec3 scale): DrawableEntity(program, drawable), __scale(scale){
    }

    virtual void addToWorld(rp3d::DynamicsWorld *world, glm::vec3 pos) {
        __world = world;
        auto transform = rp3d::Transform(rp3d::Vector3(pos.x, pos.y, pos.z), rp3d::Quaternion::identity());
        __body = world->createRigidBody(transform);
        __body->setType(rp3d::BodyType::DYNAMIC);
        __body->setUserData(this);
        setBoundingBox();
    }

    void draw() const override {
        glm::mat4 matrix;
        __program->use();
        __body->getTransform().getOpenGLMatrix(&matrix[0][0]);
        matrix = glm::scale(matrix, __scale);
        __program->setModel(matrix);

        DrawableEntity::draw();
    }

    void setPosition(glm::vec3 p) {
        auto t = __body->getTransform();
        t.setPosition(rp3d::Vector3(p.x, p.y, p.z));
        __body->setTransform(t);
    }

    void setRotation() {
        auto t = __body->getTransform();
        t.setOrientation(rp3d::Quaternion::identity());
        __body->setTransform(t);
    }

    glm::vec3 getPosition() {
        auto t = __body->getTransform().getPosition();
        return glm::vec3(t.x, t.y, t.z);
    }

    virtual ~DynamicEntity() {
        __world->destroyRigidBody(__body);
        delete __shape;
    }

};