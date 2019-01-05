#pragma once

#include <Renders/OpenGL/IBoundingBox.hpp>

#include <glad/glad.h>

namespace OpenGL {

    class CubeVAO {
        unsigned int __id;
        unsigned int __vertex, __elements;

        void loadData(float *vertices, int vsize, unsigned int *indices, int isize) {
            //VAO
            glGenVertexArrays(1, &__id);
            glBindVertexArray(__id);
            //VBO
            glGenBuffers(1, &__vertex);
            glBindBuffer(GL_ARRAY_BUFFER, __vertex);
            glBufferData(GL_ARRAY_BUFFER, vsize, vertices, GL_STATIC_DRAW);
            //EBO
            glGenBuffers(1, &__elements);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, __elements);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
            glEnableVertexAttribArray(0);
            //Unbind
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            // glDeleteBuffers(1, &__vertex);
            // glDeleteBuffers(1, &__elements);

        }

        CubeVAO(const CubeVAO &box) = delete;
    public:
        // !Todo fix this, parameters actually do nothing :))))))))))
        CubeVAO(float posx = 0, float posy = 0, float posz = 0, float size= 1) {
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

            loadData(vertices, sizeof(vertices), indices, sizeof(indices));
        }

        CubeVAO(IBoundingBox *box) {
            auto boundaries = box->getBox();

            glm::vec3 min = boundaries.first;
            glm::vec3 max = boundaries.second;

            float vertices[] = {
                min.x, min.y, max.z,
                max.x, min.y, max.z,
                max.x, max.y, max.z,
                min.x, max.y, max.z,
                min.x, min.y, min.z,
                max.x, min.y, min.z,
                max.x, max.y, min.z,
                min.x, max.y, min.z,
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

            loadData(vertices, sizeof(vertices), indices, sizeof(indices));
        }


        
        virtual ~CubeVAO() {
            glDeleteVertexArrays(1, &__id);
        }

        void draw() {
            glBindVertexArray(__id);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        }

        unsigned int getId() const { return __id; }

    };

}