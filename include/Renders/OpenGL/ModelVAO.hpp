#pragma once
#include <Renders/OpenGL/ShaderProgram.hpp>
#include <Renders/OpenGL/IProgram.hpp>
#include <Renders/OpenGL/Texture.hpp>
#include <Renders/OpenGL/Vertex.hpp>

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glad/glad.h>
namespace OpenGL {

class ModelVAO{
private:
    unsigned int __vao, __vbo, __ebo;
    ShaderProgram *__program;
    std::vector<Vertex> __vertices;
    std::vector<unsigned int> __indices;
    std::vector<Texture> __textures;

    void setupMesh()
    {
        glGenVertexArrays(1, &__vao);
        glGenBuffers(1, &__vbo);
        glGenBuffers(1, &__ebo);

        glBindVertexArray(__vao);
        glBindBuffer(GL_ARRAY_BUFFER, __vbo);

        glBufferData(GL_ARRAY_BUFFER, __vertices.size() * sizeof(Vertex), &__vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, __ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, __indices.size() * sizeof(unsigned int),
                     &__indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) nullptr);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));

        glBindVertexArray(0);
    }

public:
    ModelVAO(std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::vector<Texture> textures,
    OpenGL::ShaderProgram *program)
    {
        this->__vertices = vertices;
        this->__indices = indices;
        this->__textures = textures;
        __program = program;
        setupMesh();
    }

    int getVertexCount() const { return __vertices.size(); }
    int getIndexCount() const { return __indices.size(); }
    int getTexturesCount() const { return __textures.size(); }

    void draw() const
    {
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < __textures.size(); i++)
        {
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = __textures[i].type;
            if(name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if(name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if(name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to stream
             else if(name == "texture_height")
			    number = std::to_string(heightNr++); // transfer unsigned int to stream

            auto uniform = name + number;

            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            __textures[i].use();
            __program->uniformTexture(uniform.c_str(), i);
        }

        glBindVertexArray(__vao);
        glDrawElements(GL_TRIANGLES, __indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
};

}