#pragma once

#include <Renders/OpenGL/Geometry/IGeometry.hpp>
#include <Renders/OpenGL/Geometry/IGeometryProvider.hpp>
#include <Renders/OpenGL/Vertex.hpp>

#include <vector>

#include <glad/glad.h>


namespace OpenGL {
/**
 * \class VAO representation
 *
 * \brief holds information about data stored in GPU and knows how to draw it
 *
 * \note doesn't use EBO, just plain VBO
 */
    class VertexVAO : public IGeometry {
        int __first;
        int __count;
        GLenum __mode;

        unsigned int __id, __vbo;

        IGeometryProvider *provider;

        void destroyBuffer() {
            glDeleteBuffers(1, &__vbo);
            glDeleteVertexArrays(1, &__id);
        }

        void bufferData(const std::vector<Vertex> &data) {
            destroyBuffer();

            __first = 0;
            __count = static_cast<int>(data.size());

            glGenVertexArrays(1, &__id);
            glBindVertexArray(__id);

            glGenBuffers(1, &__vbo);
            glBindBuffer(GL_ARRAY_BUFFER, __vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(data) * sizeof(Vertex), &data[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));

            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, tangent));

            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, bitangent));

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
public:
    VertexVAO(IGeometryProvider *provider, GLenum mode = GL_TRIANGLES) {
        bufferData(provider->getData());
        setMode(mode);
    }

    void update() {
        bufferData(provider->getData());
    }

    virtual ~VertexVAO() {
        destroyBuffer();
    }

    int getFirst() const {
        return __first;
    }

    void setFirst(int __first) {
        VertexVAO::__first = __first;
    }

    int getCount() const {
        return __count;
    }

    void setCount(int __count) {
        VertexVAO::__count = __count;
    }

    GLenum getMode() const {
        return __mode;
    }

    void setMode(GLenum __mode) {
        VertexVAO::__mode = __mode;
    }

    void draw() const override {
        draw(__mode, __first, __count);
    }

    void draw(GLenum mode, int first, int count) const override {
        glDrawArrays(mode, first, static_cast<unsigned int>(count));
    }
  };

}
