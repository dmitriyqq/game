#pragma once

#include <Renders/OpenGL/Geometry/IGeometry.hpp>
#include <Renders/OpenGL/Geometry/IGeometryProvider.hpp>
#include <Renders/OpenGL/Geometry/VertexVAO.hpp>
#include <Renders/OpenGL/Vertex.hpp>

#include <cstddef>
#include <vector>
#include <glad/glad.h>


namespace OpenGL {
    class VectorDebug : public IGeometryProvider, public VertexVAO {
        float __x, __y, __z;
    public:
        VectorDebug(float x, float y, float z): __x(x), __y(y), __z(z),  VertexVAO(this) {}

        virtual std::vector<Vertex> getData() const override {
            std::vector <Vertex> vec;
            vec.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
            vec.emplace_back(glm::vec3(glm::vec3(__x, __y, __z)));
            return vec;
        }

        float getX() const {
            return __x;
        }

        void setX(float __x) {
            VectorDebug::__x = __x;
            update();
        }

        float getY() const {
            return __y;
        }

        void setY(float __y) {
            VectorDebug::__y = __y;
            update();
        }

        float getZ() const {
            return __z;
        }

        void setZ(float __z) {
            VectorDebug::__z = __z;
            update();
        }
    };

}