#pragma once

#include "DynamicEntity.hpp"
#include "../Logic/Job.hpp"

class UnitsFactory;

class Unit: public DynamicEntity {
    std::string __name;
    friend class UnitsFactory;
    Job *__job = nullptr;

    void moveTo(float x, float z) {
        auto force = glm::vec3(x, 0, z) - getPosition();
        force = (float)(std::pow(glm::length(force), 1.02f)) * glm::normalize(force);
        __body->applyForceToCenterOfMass(rp3d::Vector3(force.x, force.y, force.z));
        rp3d::Quaternion q;
        auto v1 = glm::vec3(1.0f, 0.0f, 0.0f);
        auto v2 = -force;
        auto a = glm::cross(v1, v2);
        q.x = a.x;
        q.y = a.y;
        q.z = a.z;
        q.w = sqrt((glm::length(v1) * glm::length(v1) ) * (glm::length(v2) * glm::length(v2))) + glm::dot(v1, v2);
        __body->setTransform(rp3d::Transform(__body->getTransform().getPosition(), q));
    }

public:
    Unit(OpenGL::PositionShaderProgram *program, OpenGL::IBoundingBoxDrawable *drawable, glm::vec3 scale, const std::string & name):
     DynamicEntity(program, drawable, scale), __name(name) {

    }

    void setJob(Job *job) {
        delete __job;
        __job = job;
    }

    Type getType() override {
        return Type::UNIT;
    }

    const char* getName() override {
        return __name.c_str();
    }

    void stopMoving() {
        __body->setLinearVelocity(rp3d::Vector3::zero());
    }

    bool isInArea(float r1left, float r1top, float r1right, float r1bottom) {
        auto box = __drawable->getBox();

        auto p = __body->getTransform().getPosition();
        float dx = (box.second.x - box.first.x) / 2.0f;
        float dz = (box.second.z - box.first.z) / 2.0f;

        float r2left = p.x - dx;
        float r2right = p.x + dx;
        float r2top = p.z - dz;
        float r2bottom = p.z + dz;

        return !(r2left > r1right ||
                 r2right < r1left ||
                 r2top > r1bottom ||
                 r2bottom < r1top);
    }

    void update(float delta_time) override {
        if (__job != nullptr) {
            auto jobType = __job->getType();
            switch (jobType) {
                case Job::Type::MOVE:
                    auto moveJob = dynamic_cast<MoveToJob*>(__job);
                    moveJob->setProgress(getPosition());
                    if (!moveJob->isCompleted()) {
                        moveTo(moveJob->__target.x, moveJob->__target.z);
                    } else {
                        stopMoving();
                    }
            }
        } else {
            __body->applyForceToCenterOfMass(rp3d::Vector3(-0.1f, 0, 0));
        }
    }
};
