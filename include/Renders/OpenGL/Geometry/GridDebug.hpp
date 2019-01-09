#pragma once

#include <Renders/OpenGL/ColorVertex.hpp>
#include <Renders/OpenGL/Geometry/IGeometryProvider.hpp>
#include <Renders/OpenGL/Geometry/VertexVAO.hpp>

namespace OpenGL{

class GridDebug: public IGeometryProvider<ColorVertex>, public VertexVAO<ColorVertex> {

    float __size_x, __size_y, __size_z;

    float __cell_size;

    glm::vec3 COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
public:
    GridDebug(float sx, float sy, float sz, float cell_size):
            __size_x(sx),
            __size_y(sy),
            __size_z(sz),
            __cell_size(cell_size),
            VertexVAO<ColorVertex>(this, GL_LINES) {

    }

    std::vector<ColorVertex> getData() const override {
        auto vert = std::vector<ColorVertex>();

        for (float i = -__size_x; i <  __size_x; i+=__cell_size) {
            vert.emplace_back(glm::vec3(i, 0.0f, -__size_z), COLOR);
            vert.emplace_back(glm::vec3(i, 0.0f, __size_z), COLOR);
        }

        for (float i = -__size_z; i <  __size_z; i+=__cell_size) {
            vert.emplace_back(glm::vec3(-__size_x, 0.0f, i), COLOR);
            vert.emplace_back(glm::vec3(__size_x, 0.0f, i), COLOR);
        }

        return vert;
    }
};

}
