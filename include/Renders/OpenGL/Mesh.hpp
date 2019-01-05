#pragma once

#include <Renders/IDrawable.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/OpenGL/IBoundingBox.hpp>
#include <Renders/OpenGL/ModelPosition.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <Renders/OpenGL/Materials.hpp>
#include <Renders/OpenGL/CubeNormalsVAO.hpp>

#include <vector>

namespace OpenGL {

    class Mesh : public IDrawable, public ModelPosition{
        
    protected:
        IDrawable *__drawable = nullptr;
        PositionShaderProgram *__shaderProgram = nullptr;
    public:
        Mesh(PositionShaderProgram *program, IDrawable *drawable): __shaderProgram(program) {
            __drawable = drawable;
        }

        void draw() const override {
            uniform(__shaderProgram);
            __drawable->draw();
        };
    };
};
