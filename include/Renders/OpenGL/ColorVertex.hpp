#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace OpenGL {

    struct ColorVertex {
        glm::vec3 position = glm::vec3(0);
        glm::vec3 color = glm::vec3();

        ColorVertex(glm::vec3 pos, glm::vec3 color):
            position(pos), color(color) {}

        static void defineData() {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*) offsetof(ColorVertex, color));
        }
    };

}
