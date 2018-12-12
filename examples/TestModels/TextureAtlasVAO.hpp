#pragma once
#include <vector>
#include "Frame.hpp"
#include "ImageAtlas.hpp"

class TextureAtlasVAO {
    unsigned int __id;
    unsigned int __vertex, __elements;
public:
    TextureAtlasVAO(std::vector<Frame> &frames, float width, float height, unsigned int id) {

        glGenVertexArrays(1, &__id);
        glBindVertexArray(__id);

        glGenBuffers(1, &__vertex);

        // auto frames = atlas->getFrames();

        float vertices[frames.size() * 6 * 4];

        // float width = atlas->getWidth();
        // float height = atlas->getHeight();

        for(int j = 0, i = 0; j < (int)frames.size(); j++) {
            auto frame = frames[j];
            float x = frame.offsetX;
            float y = frame.offsetY;
            float x2 = x + frame.w;
            float y2 = y + frame.h;

            float u2 = x2 / width, v1 = y2 / height;
            float u1 = x / width, v2 = y / height;

            float a = frame.h / frame.w;
            float h1 = 1.0f * a / 2.0f;
            float w1 = 0.5;

            vertices[i+0] = -w1;
            vertices[i+1] = -h1;
            vertices[i+2] = u1;
            vertices[i+3] = v1;
            i+=4;
            vertices[i+0] = w1;
            vertices[i+1] = -h1;
            vertices[i+2] = u2;
            vertices[i+3] = v1;
            i+=4;
            vertices[i+0] = -w1;
            vertices[i+1] = h1;
            vertices[i+2] = u1;
            vertices[i+3] = v2;
            i+=4;

            vertices[i+0] = -w1;
            vertices[i+1] = h1;
            vertices[i+2] = u1;
            vertices[i+3] = v2;
            i+=4;
            vertices[i+0] = w1;
            vertices[i+1] = -h1;
            vertices[i+2] = u2;
            vertices[i+3] = v1;
            i+=4;
            vertices[i+0] = w1;
            vertices[i+1] = h1;
            vertices[i+2] = u2;
            vertices[i+3] = v2;
            i+=4;
        }

        glBindBuffer(GL_ARRAY_BUFFER, __vertex);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //Unbind
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    virtual ~TextureAtlasVAO() {
        glDeleteVertexArrays(1, &__id);
    }

    void draw(int offset) {
        glBindVertexArray(__id);
        glDrawArrays(GL_TRIANGLES, offset * 6, 6);
    }

    unsigned int getId() const { return __id; }
};