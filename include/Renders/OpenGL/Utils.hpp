#pragma once 

/**
 * \class BoundingBox
 *
 * \brief helper functions for OpenGL and glm
 *
 * This class contains static methods for various glm transformations
 * 
 * \note it needs to fix resource release
 */

#include <glm/glm.hpp>

namespace OpenGL{

class Utils {
public:
    static glm::vec2 min(const glm::vec2 &a, const glm::vec2 &b){
        return glm::vec2(std::min(a.x, b.x), std::min(a.y, b.y));
    }

    static glm::vec2 max(const glm::vec2 &a, const glm::vec2 &b){
        return glm::vec2(std::max(a.x, b.x), std::max(a.y, b.y));
    }
};

}
