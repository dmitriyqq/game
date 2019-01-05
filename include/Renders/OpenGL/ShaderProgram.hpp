#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include "Materials.hpp"
#include <Renders/OpenGL/Shader.hpp>
#include <Renders/OpenGL/ICamera.hpp>
#include <Renders/OpenGL/IProgram.hpp>

namespace OpenGL {

using std::string;

class ShaderProgram: public IProgram {
    unsigned int __id;
    int __screenWidth, __screenHeight;
    ICamera *__camera = nullptr;
public:
    void loadShaders(const string &vertexSrc, const string &fragmentSrc) {
        Shader vertShader = Shader(vertexSrc, GL_VERTEX_SHADER);
        Shader fragShader = Shader(fragmentSrc, GL_FRAGMENT_SHADER);

        __id = glCreateProgram();
        glAttachShader(__id, vertShader.getId());
        glAttachShader(__id, fragShader.getId());
        glLinkProgram(__id);
    }

    unsigned int getId() const { return __id; }

    void use() const override { glUseProgram(__id); }

    ShaderProgram() = default;

    virtual ~ShaderProgram() = default;

    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(__id, name.c_str()), (int) value);
    }

    void setInt(const std::string &name, int value) const {
        use();
        glUniform1i(glGetUniformLocation(__id, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        use();
        glUniform1f(glGetUniformLocation(__id, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(__id, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(__id, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(__id, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const {
        use();
        glUniform3f(glGetUniformLocation(__id, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(__id, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(__id, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(__id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(__id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        use();
        glUniformMatrix4fv(glGetUniformLocation(__id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void uniformTexture(const std::string &name, int i) const {
        use();
        glUniform1i(glGetUniformLocation(__id, name.c_str()), i);
    } 

    void setMaterial(const Material &material){
        use();
        setVec3("material.diffuse", material.diffuse);
        setVec3("material.specular", material.specular);
        setFloat("material.shininess", material.shininess);
    }

    void setCamera(ICamera *camera, int width, int height){
        __camera = camera;
        __screenWidth = width;
        __screenHeight = height;

        use();
        setMat4("view", camera->getViewMatrix());
        setMat4("projection", camera->getProjectionMatrix(width, height));
    }

    int getWidth() {
        return __screenWidth;
    }

    int getHeight() {
        return __screenHeight;
    }

    ICamera* getCamera() const {
        return __camera;
    }
};

}
