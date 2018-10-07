#include "Renders/OpenGL/CubeVAO.hpp"
#include <glad/glad.h>

namespace OpenGL {
    CubeVAO::CubeVAO() {
        float vertices[] = {
                -0.5, -0.5, 0.5,
                0.5, -0.5, 0.5,
                0.5, 0.5, 0.5,
                -0.5, 0.5, 0.5,
                -0.5, -0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, 0.5, -0.5,
                -0.5, 0.5, -0.5
        };

        unsigned int indices[] = {
                0, 1, 2,
                0, 2, 3,
                1, 2, 6,
                1, 5, 6,
                5, 6, 7,
                4, 5, 7,
                3, 4, 7,
                0, 3, 4,
                2, 3, 7,
                2, 6, 7,
                0, 4, 5,
                0, 1, 5
        };


        //VAO
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
        //VBO
        glGenBuffers(1, &myBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, myBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //EBO
        glGenBuffers(1, &myElemBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myElemBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        //Unbind
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // glDeleteBuffers(1, &myBuffer);
        // glDeleteBuffers(1, &myElemBuffer);
    }

    CubeVAO::~CubeVAO() {
        glDeleteVertexArrays(1, &m_id);
    }

    void CubeVAO::draw() {
        glBindBuffer(GL_ARRAY_BUFFER, myBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myElemBuffer);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}