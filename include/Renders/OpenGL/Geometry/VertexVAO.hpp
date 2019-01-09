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
 * the parameter of template is Vertex class that defines 'void defineData(void)' function
 *
 * \note doesn't use EBO, just plain VBO
 */
    template<class V>
    class VertexVAO : public IGeometry, public IDrawable {
        int __first;
        int __count;
        GLenum __mode;

        unsigned int __id, __vbo;

        bool __data = false;

        IGeometryProvider<V> *__provider = nullptr;

        void destroyBuffer() {
            if (__data) {
                glDeleteBuffers(1, &__vbo);
                glDeleteVertexArrays(1, &__id);
                __data = false;
            }
        }

        void bufferData(const std::vector<V> &data) {
            if (__data) {
                updateData(data);
                return;
            }

            __data = true;

            __first = 0;
            __count = static_cast<int>(data.size());

            glGenVertexArrays(1, &__id);
            glBindVertexArray(__id);

            glGenBuffers(1, &__vbo);
            glBindBuffer(GL_ARRAY_BUFFER, __vbo);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(V), &data[0], GL_STATIC_DRAW);

            V::defineData();

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void updateData(const std::vector<V> &data) {
            glBindVertexArray(__id);
            glBindBuffer(GL_ARRAY_BUFFER, __vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(V), &data[0]);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
public:
    // Fuck shit you can't call virtual methods in constructor
    VertexVAO(IGeometryProvider<V> *provider, GLenum mode = GL_TRIANGLES):
    __provider(provider)
    {
        setMode(mode);
    }

    void update() {
        VertexVAO::bufferData(__provider->getData());
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
        glBindVertexArray(__id);
        glBindBuffer(GL_ARRAY_BUFFER, __vbo);
        glDrawArrays(mode, first, static_cast<unsigned int>(count));
    }
  };

}
