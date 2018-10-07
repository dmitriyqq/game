#pragma once

#include <glm/detail/type_mat.hpp>

namespace OpenGL{
    class ICamera{
    public:
        virtual glm::mat4 getViewMatrix() = 0;

        virtual glm::mat4 getProjectionMatrix(float width, float height) = 0;
    };
}
