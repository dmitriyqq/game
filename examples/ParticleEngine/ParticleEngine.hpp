#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <random>

class ParticleEngine {
    int __size;
    std::uniform_real_distribution<float> __dist;
    std::mt19937 __rnd;

    glm::vec3 __origin;

    unsigned int __billboard_vbo, __positions_vbo, __colors_vbo;
    unsigned int __vao;

    glm::vec4 *__positions;
    glm::vec4 * __colors;
    glm::vec3 * __velocities;
    float *__life;
public:
    void generateVAO() {
        static const GLfloat g_vertex_buffer_data[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
        };

        glGenVertexArrays(1, &__vao);
        glBindVertexArray(__vao);

        glGenBuffers(1, &__billboard_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, __billboard_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        // The VBO containing the positions and sizes of the particles
        glGenBuffers(1, &__positions_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, __positions_vbo);
        // Initialize with empty (NULL) buffer : it will be updated later, each frame.
        glBufferData(GL_ARRAY_BUFFER, __size * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);

        // The VBO containing the colors of the particles
        glGenBuffers(1, &__colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, __colors_vbo);
        // Initialize with empty (NULL) buffer : it will be updated later, each frame.
        glBufferData(GL_ARRAY_BUFFER, __size * 4 * sizeof(GLubyte), nullptr, GL_STREAM_DRAW);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, __billboard_vbo);
        glVertexAttribPointer(
                0, // attribute. No particular reason for 0, but must match the layout in the shader.
                3, // size
                GL_FLOAT, // type
                GL_FALSE, // normalized?
                0, // stride
                (void*)0 // array buffer offset
        );

        // 2nd attribute buffer : positions of particles' centers
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, __positions_vbo);
        glVertexAttribPointer(
                1, // attribute. No particular reason for 1, but must match the layout in the shader.
                4, // size : x + y + z + size => 4
                GL_FLOAT, // type
                GL_FALSE, // normalized?
                0, // stride
                (void*)0 // array buffer offset
        );

        // 3rd attribute buffer : particles' colors
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, __colors_vbo);
        glVertexAttribPointer(
                2, // attribute. No particular reason for 1, but must match the layout in the shader.
                4, // size : r + g + b + a => 4
                GL_UNSIGNED_BYTE, // type
                GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
                0, // stride
                (void*)0 // array buffer offset
        );
        glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
        glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
        glVertexAttribDivisor(2, 1); // color : one per quad -> 1
        glBindVertexArray(0);
    }

    inline void createParticle(glm::vec4 &position, glm::vec4 &color, glm::vec3 &velocity, float &life){
        position = glm::vec4(__origin.x, __origin.y, __origin.z, 0.0f);
        color = glm::vec4(1.0f, 0.01f, 0.01f, 1.0f);
        velocity = glm::vec3(10.0f * __dist(__rnd), 10.0f * __dist(__rnd), 0.03f * __dist(__rnd));
        position.w = 0.05f * __dist(__rnd);
        velocity.z = 0.0f;
        life = 2.0f * __dist(__rnd) + 1.0f;
    }

    ParticleEngine(int numParticles, glm::vec3 origin): __size(numParticles) {
        __positions = new glm::vec4[numParticles];
        __colors =  new glm::vec4[numParticles];
        __velocities = new glm::vec3[numParticles];
        __life = new float[numParticles];

        generateVAO();

        for(int i = 0; i < __size; i++) {
            createParticle(__positions[i], __colors[i], __velocities[i], __life[i]);
        }

        glBindBuffer(GL_ARRAY_BUFFER, __colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, __size * 4 * sizeof(GLubyte), nullptr, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
        glBufferSubData(GL_ARRAY_BUFFER, 0, __size * sizeof(GLubyte) * 4, &__colors[0]);
    }

    void update (float deltaTime) {
        for(int i = 0; i < __size; i++) {
            auto t = deltaTime * __velocities[i];
            if(__life[i] < 0) {
                createParticle(__positions[i], __colors[i], __velocities[i], __life[i]);
            } else {
                __positions[i].x += t.x;
                __positions[i].y += t.y;
                __positions[i].z += t.z;
                __life[i] -= deltaTime;

                if (__colors[i].g > 0.1)
                    __colors[i].g -=  deltaTime;
                __colors[i].r = 1.0f;
            }
        }

        glBindBuffer(GL_ARRAY_BUFFER, __positions_vbo);
        glBufferData(GL_ARRAY_BUFFER, __size * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
        glBufferSubData(GL_ARRAY_BUFFER, 0, __size * sizeof(GLfloat) * 4, &__positions[0]);

        glBindBuffer(GL_ARRAY_BUFFER, __colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, __size * 4 * sizeof(GLubyte), nullptr, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
        glBufferSubData(GL_ARRAY_BUFFER, 0, __size * sizeof(GLubyte) * 4, &__colors[0]);
    }

    void draw () const {
        glBindVertexArray(__vao);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, __size);
    }

    ~ParticleEngine() {
        delete[] __positions;
        delete[] __colors;
        delete[] __velocities;
    }
};
