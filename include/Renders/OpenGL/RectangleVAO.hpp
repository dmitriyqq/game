#pragma once
#include <glad/glad.h>
#include <Renders/IDrawable.hpp>


namespace OpenGL {
    class RectangleVAO : public IDrawable {
        unsigned int __id, __vertex;
        public:
        RectangleVAO() {
            float vertices[] = {
                // positions          // colors           // texture coords
                -1.0f,  -1.0f, 0.0f,  // top right
                -1.0f, 0.0f, 0.0f,  // bottom right
                0.0f, 0.0f, 0.0f,  // bottom left
                0.0f,  -1.0f, 0.0f,  // top left 
                0.0f, 0.0f, 0.0f,  // bottom left
                -1.0f,  -1.0f, 0.0f,  // top right
            };

             //VAO
            glGenVertexArrays(1, &__id);
            glBindVertexArray(__id);
            //VBO
            glGenBuffers(1, &__vertex);
            glBindBuffer(GL_ARRAY_BUFFER, __vertex);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            //EBO
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
            glEnableVertexAttribArray(0);
            //Unbind
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // glDeleteBuffers(1, &__vertex);
            // glDeleteBuffers(1, &__elements);
        }

        void draw() const {
            glBindVertexArray(__id);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    };  
}