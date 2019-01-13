#pragma once

#include <glm/glm.hpp>

class Job {
public:
    enum class Type {
        MOVE, ATTACK
    };

    virtual bool isCompleted() = 0;

    virtual Type getType() = 0;
};


class MoveToJob: public Job{
public:
    glm::vec3 __target;
    glm::vec3 __progress;

    MoveToJob(glm::vec3 target): __target(target) {

    }

    Job::Type getType() {
        return Job::Type::MOVE;
    };

    bool isCompleted() {
        auto d = __target - __progress;
        return glm::length(d) < 10.0f;
    }


    void setProgress(glm::vec3 position) {
        __progress = position;
    }

};

