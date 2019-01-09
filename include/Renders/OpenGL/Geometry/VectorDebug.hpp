#pragma once

#include <Renders/OpenGL/Geometry/IGeometry.hpp>
#include <Renders/OpenGL/Geometry/IGeometryProvider.hpp>
#include <Renders/OpenGL/Geometry/VertexVAO.hpp>
#include <Renders/OpenGL/ColorVertex.hpp>

#include <cstddef>
#include <vector>
#include <glad/glad.h>


namespace OpenGL {
    class VectorDebug : public IGeometryProvider<ColorVertex>, public VertexVAO<ColorVertex> {
        float __x1, __y1, __z1;
        float __x2, __y2, __z2;
        glm::vec3 __color;
    public:
        VectorDebug(float x1, float y1, float z1, float x2, float y2, float z2, glm::vec3 color = glm::vec3(1.0f, 0.0f, 1.0f)):
            __x1(x1), __y1(y1), __z1(z1),  __color(color),
            __x2(x2), __y2(y2), __z2(z2),  VertexVAO<ColorVertex>(this, GL_LINES) {}

        virtual std::vector<ColorVertex> getData() const override {
            std::vector <ColorVertex> vec;
            vec.emplace_back(glm::vec3(__x1, __y1, __z1), __color);
            vec.emplace_back(glm::vec3(__x2, __y2, __z2), __color);
            return vec;
        }

        void update(float x1, float y1, float z1, float x2, float y2, float z2) {
            __x1 = x1;
            __y1 = y1;
            __z1 = z1;
            __x2 = x2;
            __y2 = y2;
            __z2 = z2;
            VertexVAO::update();
        }

        void update() {
            VertexVAO::update();
        }
    };

}