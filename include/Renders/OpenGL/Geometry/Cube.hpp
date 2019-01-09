#pragma once

#include <Renders/OpenGL/ColorVertex.hpp>
#include <Renders/OpenGL/Geometry/IGeometryProvider.hpp>
#include <Renders/OpenGL/Geometry/VertexVAO.hpp>

namespace OpenGL {

class Cube: public IGeometryProvider<ColorVertex>, public VertexVAO<ColorVertex>  {
    glm::vec3 COLOR = glm::vec3(0.0f, 0.0f, 1.0f);
public:
    Cube():
        VertexVAO<ColorVertex>(this, GL_LINES) {
    }

    std::vector<ColorVertex> getData() const override {
        auto vert = std::vector<ColorVertex>();
        vert.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f), COLOR);
        vert.emplace_back(glm::vec3(0.5f, -0.5f, -0.5f), COLOR);
        vert.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f), COLOR);
        vert.emplace_back(glm::vec3(-0.5f, 0.5f, -0.5f), COLOR);
        vert.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f), COLOR);
        vert.emplace_back(glm::vec3(-0.5f, -0.5f, 0.5f), COLOR);

        vert.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), COLOR);
        vert.emplace_back(glm::vec3(-0.5f, 0.5f, 0.5f), COLOR);
        vert.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), COLOR);
        vert.emplace_back(glm::vec3(0.5f, -0.5f, 0.5f), COLOR);
        vert.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), COLOR);
        vert.emplace_back(glm::vec3(0.5f, 0.5f, -0.5f), COLOR);

        vert.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), COLOR);
        vert.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), COLOR);

        vert.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), COLOR);
        vert.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), COLOR);

        return vert;
    }
};

}
