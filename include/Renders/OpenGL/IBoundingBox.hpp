#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace OpenGL{

class IBoundingBox {
    public:
        virtual std::pair<glm::vec3, glm::vec3> getBox() const = 0;
};

}