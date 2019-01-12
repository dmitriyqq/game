#pragma once

#include <Renders/OpenGL/ColorVertex.hpp>
#include <Renders/OpenGL/Geometry/IGeometryProvider.hpp>
#include <Renders/OpenGL/Geometry/VertexVAO.hpp>

namespace OpenGL {

class RectangleXZ: public IGeometryProvider<ColorVertex>, public VertexVAO<ColorVertex>  {
public:
    float __x1, __z1, __x2, __z2;
    glm::vec3 COLOR = glm::vec3(0.0f, 1.0f, 0.0f);
public:
    RectangleXZ(float x1, float z1, float x2, float z2):
            __x1(x1),
            __z1(z1),
            __x2(x2),
            __z2(z2),
            VertexVAO<ColorVertex>(this, GL_LINES) {

    }

    std::vector<ColorVertex> getData() const override {
        auto vert = std::vector<ColorVertex>();
        vert.emplace_back(glm::vec3(__x1, 0.0f, __z1), COLOR);
        vert.emplace_back(glm::vec3(__x2, 0.0f, __z1), COLOR);

        vert.emplace_back(glm::vec3(__x1, 0.0f, __z1), COLOR);
        vert.emplace_back(glm::vec3(__x1, 0.0f, __z2), COLOR);

        vert.emplace_back(glm::vec3(__x1, 0.0f, __z2), COLOR);
        vert.emplace_back(glm::vec3(__x2, 0.0f, __z2), COLOR);

        vert.emplace_back(glm::vec3(__x2, 0.0f, __z1), COLOR);
        vert.emplace_back(glm::vec3(__x2, 0.0f, __z2), COLOR);
        return vert;
    }

    void update(float x1, float z1, float x2, float z2) {
        __x1 = x1;
        __z1 = z1;
        __x2 = x2;
        __z2 = z2;
        VertexVAO::update();
    }
};

}
