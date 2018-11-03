#pragma once

#include <glm/detail/type_mat.hpp>
#include <glm/vec3.hpp>

namespace OpenGL{
    class ICamera{
    public:
        virtual glm::mat4 getViewMatrix() const = 0;

        virtual glm::mat4 getProjectionMatrix(float width, float height) const = 0;

        virtual void setPosition(glm::vec3 position) = 0;
    };
}
