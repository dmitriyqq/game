#include <glad/glad.h>
#include <string>

#include "Renders/OpenGL/ShaderProgram.hpp"
#include "Renders/OpenGL/Shader.hpp"

namespace OpenGL {

    ShaderProgram::ShaderProgram() {

    }

    ShaderProgram::~ShaderProgram() {

    }

    void ShaderProgram::loadShaders(string const &vertexSrc, string const &fragmentSrc) {
        Shader vertShader = Shader(vertexSrc, GL_VERTEX_SHADER);
        Shader fragShader = Shader(fragmentSrc, GL_FRAGMENT_SHADER);

        m_id = glCreateProgram();
        glAttachShader(m_id, vertShader.getId());
        glAttachShader(m_id, fragShader.getId());
        glLinkProgram(m_id);
    }

}