#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include "Materials.hpp"
#include <Renders/OpenGL/ICamera.hpp>

namespace OpenGL {

using std::string;

class ShaderProgram {
public:
    void loadShaders(const string &vertexSrc, const string &fragmentSrc);

    unsigned int getId() const { return m_id; }

    void use() const { glUseProgram(m_id); }

    ShaderProgram();

    virtual ~ShaderProgram();

    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int) value);
    }

    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMaterial(const Material &material){
        setVec3("material.diffuse", material.diffuse);
        setVec3("material.specular", material.specular);
        setFloat("material.shininess", material.shininess);
    }

    void setCamera(const ICamera *camera, int width, int height){
        setMat4("view", camera->getViewMatrix());
        setMat4("projection", camera->getProjectionMatrix(width, height));
    }

private:
    unsigned int m_id;
};

}
