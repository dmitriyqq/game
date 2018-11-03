#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "Materials.hpp"
#include "CubeNormalsVAO.hpp"
#include "ShaderProgram.hpp"
#include "../IDrawable.hpp"
#include <vector>

namespace OpenGL {
    class CubeMesh : public IDrawable{
        CubeNormalsVAO __vao;
    protected:
        Material __material;
        static ShaderProgram *__shaderProgram;
        glm::mat4 __model;

        int generateCubeVAO(float posx, float posy, float posz, float size, std::vector<float> &outVerticies){
            float hs = size / 2;
            std::vector<float> tmp = {
                    // positions          // normals
                    posx - hs, posy - hs, posz - hs,  0.0f,  0.0f, -1.0f,
                    posx + hs, posy - hs, posz - hs,  0.0f,  0.0f, -1.0f,
                    posx + hs, posy + hs, posz - hs,  0.0f,  0.0f, -1.0f,
                    posx + hs, posy + hs, posz - hs,  0.0f,  0.0f, -1.0f,
                    posx - hs, posy + hs, posz - hs,  0.0f,  0.0f, -1.0f,
                    posx - hs, posy - hs, posz - hs,  0.0f,  0.0f, -1.0f,
                    posx - hs, posy - hs, posz + hs,  0.0f,  0.0f, 1.0f,
                    posx + hs, posy - hs, posz + hs,  0.0f,  0.0f, 1.0f,
                    posx + hs, posy + hs, posz + hs,  0.0f,  0.0f, 1.0f,
                    posx + hs, posy + hs, posz + hs,  0.0f,  0.0f, 1.0f,
                    posx - hs, posy + hs, posz + hs,  0.0f,  0.0f, 1.0f,
                    posx - hs, posy - hs, posz + hs,  0.0f,  0.0f, 1.0f,
                    posx - hs, posy + hs, posz + hs, -1.0f,  0.0f,  0.0f,
                    posx - hs, posy + hs, posz - hs, -1.0f,  0.0f,  0.0f,
                    posx - hs, posy - hs, posz - hs, -1.0f,  0.0f,  0.0f,
                    posx - hs, posy - hs, posz - hs, -1.0f,  0.0f,  0.0f,
                    posx - hs, posy - hs, posz + hs, -1.0f,  0.0f,  0.0f,
                    posx - hs, posy + hs, posz + hs, -1.0f,  0.0f,  0.0f,
                    posx + hs, posy + hs, posz + hs,  1.0f,  0.0f,  0.0f,
                    posx + hs, posy + hs, posz - hs,  1.0f,  0.0f,  0.0f,
                    posx + hs, posy - hs, posz - hs,  1.0f,  0.0f,  0.0f,
                    posx + hs, posy - hs, posz - hs,  1.0f,  0.0f,  0.0f,
                    posx + hs, posy - hs, posz + hs,  1.0f,  0.0f,  0.0f,
                    posx + hs, posy + hs, posz + hs,  1.0f,  0.0f,  0.0f,
                    posx - hs, posy - hs, posz - hs,  0.0f, -1.0f,  0.0f,
                    posx + hs, posy - hs, posz - hs,  0.0f, -1.0f,  0.0f,
                    posx + hs, posy - hs, posz + hs,  0.0f, -1.0f,  0.0f,
                    posx + hs, posy - hs, posz + hs,  0.0f, -1.0f,  0.0f,
                    posx - hs, posy - hs, posz + hs,  0.0f, -1.0f,  0.0f,
                    posx - hs, posy - hs, posz - hs,  0.0f, -1.0f,  0.0f,
                    posx - hs, posy + hs, posz - hs,  0.0f,  1.0f,  0.0f,
                    posx + hs, posy + hs, posz - hs,  0.0f,  1.0f,  0.0f,
                    posx + hs, posy + hs, posz + hs,  0.0f,  1.0f,  0.0f,
                    posx + hs, posy + hs, posz + hs,  0.0f,  1.0f,  0.0f,
                    posx - hs, posy + hs, posz + hs,  0.0f,  1.0f,  0.0f,
                    posx - hs, posy + hs, posz - hs,  0.0f,  1.0f,  0.0f,
            };

            outVerticies.insert(outVerticies.end(),tmp.begin(), tmp.end());
            return (int) tmp.size();
        };

    public:
        CubeMesh(): __model(1) { }

        void setColor(float r, float g, float b){
            __shaderProgram->use();
            __material.shininess = 0.7;
            __material.specular = glm::vec3(r, g, b);
            __material.diffuse = glm::vec3(r, g, b);
            __shaderProgram->setMaterial(__material);
        }

        static void useProgram(ShaderProgram *program){
            __shaderProgram = program;
        }

        virtual void draw(IWindow *window){
            __shaderProgram->use();
            __vao.draw();
        };

        void translate(float x, float y, float z){
            __model = glm::translate(__model, glm::vec3(x, y, z));
        }

        void setPosition(int x, int y, int z){
            // !TODO fix restoring rotation and scale;
            // For now I need only to translate.
            __shaderProgram->use();

            __model = glm::mat4(1);
            __model = glm::translate(__model, glm::vec3(x, y, z));

            __shaderProgram->setMat4("model", __model);
        }
    };

    ShaderProgram* CubeMesh::__shaderProgram = nullptr;
}

