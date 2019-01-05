#pragma once

#include <glm/glm.hpp>

namespace OpenGL {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoords, glm::vec3 Tangent = glm::vec3(), glm::vec3 Bitangent = glm::vec3()):
            position(pos), normal(normal), texCoords(texCoords), tangent(Tangent), bitangent(Bitangent) {}
};

}