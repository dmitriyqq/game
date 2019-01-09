#pragma once

#include <Renders/OpenGL/ColorVertex.hpp>
#include <Renders/OpenGL/Geometry/IGeometryProvider.hpp>
#include <Renders/OpenGL/Geometry/VertexVAO.hpp>

namespace OpenGL{

class AxiesDebug: public IGeometryProvider<ColorVertex>, public VertexVAO<ColorVertex> {
    float __size_x, __size_y, __size_z;

    glm::vec3 X_COLOR = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 Y_COLOR = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 Z_COLOR = glm::vec3(0.0f, 1.0f, 0.0f);
public:
    AxiesDebug(float sx, float sy, float sz):
        __size_x(sx),
        __size_y(sy),
        __size_z(sz),
        VertexVAO<ColorVertex>(this, GL_LINES) {

    }

    std::vector<ColorVertex> getData() const override {
        auto vert = std::vector<ColorVertex>();
        vert.emplace_back(glm::vec3(-__size_x,0,0), X_COLOR);
        vert.emplace_back(glm::vec3(__size_x,0,0), X_COLOR);

        vert.emplace_back(glm::vec3(0, -__size_y, 0), Y_COLOR);
        vert.emplace_back(glm::vec3(0, __size_y, 0), Y_COLOR);

        vert.emplace_back(glm::vec3(0, 0, -__size_z), Z_COLOR);
        vert.emplace_back(glm::vec3(0, 0, __size_z), Z_COLOR);
        return vert;
    }
};

}