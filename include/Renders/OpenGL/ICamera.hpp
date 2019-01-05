#pragma once

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

namespace OpenGL{
    class ICamera{
    public:
        virtual glm::mat4 getViewMatrix() const = 0;

        virtual glm::mat4 getProjectionMatrix(float width, float height) const = 0;

        virtual void setPosition(glm::vec3 position) = 0;

        virtual glm::vec3 getForwardVector() const = 0;

        virtual glm::vec3 getRightVector() const = 0;

        virtual glm::vec3 getUpVector() const = 0;

        virtual glm::vec3 getPosition() const = 0;
    };
}
