#pragma once

#include <glm/glm.hpp>

namespace OpenGL {

class IPositionProvider {
    public:
        virtual glm::mat4 getPositionMatrix() const = 0;

        virtual glm::vec3 getPostionVector() const = 0;
};

}