#pragma once

#include <glad/glad.h>
namespace OpenGL {

    class CubeNormalsVAO{
        unsigned int __vao;
        unsigned int __vbuffer;
    public:
        CubeNormalsVAO(float posx = 0, float posy = 0, float posz = 0, float size= 1){
//            float hs = size/2;
//
//            float vertices[] = {
//                    // positions          // normals
//                    posx - hs, posy - hs, posz - hs,  0.0f,  0.0f, -1.0f,
//                    posx + hs, posy - hs, posz - hs,  0.0f,  0.0f, -1.0f,
//                    posx + hs, posy + hs, posz - hs,  0.0f,  0.0f, -1.0f,
//                    posx + hs, posy + hs, posz - hs,  0.0f,  0.0f, -1.0f,
//                    posx - hs, posy + hs, posz - hs,  0.0f,  0.0f, -1.0f,
//                    posx - hs, posy - hs, posz - hs,  0.0f,  0.0f, -1.0f,
//                    posx - hs, posy - hs, posz + hs,  0.0f,  0.0f, 1.0f,
//                    posx + hs, posy - hs, posz + hs,  0.0f,  0.0f, 1.0f,
//                    posx + hs, posy + hs, posz + hs,  0.0f,  0.0f, 1.0f,
//                    posx + hs, posy + hs, posz + hs,  0.0f,  0.0f, 1.0f,
//                    posx - hs, posy + hs, posz + hs,  0.0f,  0.0f, 1.0f,
//                    posx - hs, posy - hs, posz + hs,  0.0f,  0.0f, 1.0f,
//                    posx - hs, posy + hs, posz + hs, -1.0f,  0.0f,  0.0f,
//                    posx - hs, posy + hs, posz - hs, -1.0f,  0.0f,  0.0f,
//                    posx - hs, posy - hs, posz - hs, -1.0f,  0.0f,  0.0f,
//                    posx - hs, posy - hs, posz - hs, -1.0f,  0.0f,  0.0f,
//                    posx - hs, posy - hs, posz + hs, -1.0f,  0.0f,  0.0f,
//                    posx - hs, posy + hs, posz + hs, -1.0f,  0.0f,  0.0f,
//                    posx + hs, posy + hs, posz + hs,  1.0f,  0.0f,  0.0f,
//                    posx + hs, posy + hs, posz - hs,  1.0f,  0.0f,  0.0f,
//                    posx + hs, posy - hs, posz - hs,  1.0f,  0.0f,  0.0f,
//                    posx + hs, posy - hs, posz - hs,  1.0f,  0.0f,  0.0f,
//                    posx + hs, posy - hs, posz + hs,  1.0f,  0.0f,  0.0f,
//                    posx + hs, posy + hs, posz + hs,  1.0f,  0.0f,  0.0f,
//                    posx - hs, posy - hs, posz - hs,  0.0f, -1.0f,  0.0f,
//                    posx + hs, posy - hs, posz - hs,  0.0f, -1.0f,  0.0f,
//                    posx + hs, posy - hs, posz + hs,  0.0f, -1.0f,  0.0f,
//                    posx + hs, posy - hs, posz + hs,  0.0f, -1.0f,  0.0f,
//                    posx - hs, posy - hs, posz + hs,  0.0f, -1.0f,  0.0f,
//                    posx - hs, posy - hs, posz - hs,  0.0f, -1.0f,  0.0f,
//                    posx - hs, posy + hs, posz - hs,  0.0f,  1.0f,  0.0f,
//                    posx + hs, posy + hs, posz - hs,  0.0f,  1.0f,  0.0f,
//                    posx + hs, posy + hs, posz + hs,  0.0f,  1.0f,  0.0f,
//                    posx + hs, posy + hs, posz + hs,  0.0f,  1.0f,  0.0f,
//                    posx - hs, posy + hs, posz + hs,  0.0f,  1.0f,  0.0f,
//                    posx - hs, posy + hs, posz - hs,  0.0f,  1.0f,  0.0f,
//            };
//
//            //VAO
//            glGenVertexArrays(1, &__vao);
//            glBindVertexArray(__vao);
//            //VBO
//            glGenBuffers(1, &__vbuffer);
//            glBindBuffer(GL_ARRAY_BUFFER, __vbuffer);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//            //position
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
//            glEnableVertexAttribArray(0);
//            //normal
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//            glEnableVertexAttribArray(1);
//            //Unbind
//            glBindVertexArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        virtual ~CubeNormalsVAO(){
            glDeleteBuffers(1, &__vbuffer);
            glDeleteVertexArrays(1, &__vao);
        }

        void draw(){
            glBindVertexArray(__vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        unsigned int getId() const { return __vao; }

    };
}