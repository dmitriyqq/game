#pragma once

#include <Renders/OpenGL/IPositionProvider.hpp>
#include <Renders/OpenGL/ShaderProgram.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace OpenGL{

class ModelPosition : public IPositionProvider {
    glm::vec3 __position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 __scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 __rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 __model = glm::mat4(1.0f);
    float __angle = 0.0f;

public:
    ModelPosition() = default;

    ModelPosition(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation):
        __position(pos), __scale(scale), __rotation(rotation)
    {
    }

    void uniform(OpenGL::ShaderProgram *program) const {
        program->setMat4("model", __model);
    }

    void translate(float x, float y, float z){
        __position += glm::vec3(x, y, z);
        updateModel();
    }

    void setPosition(float x, float y, float z){
        __position = glm::vec3(x, y, z);
        updateModel();
    }

    void setScale(float x, float y, float z) {
        __scale = glm::vec3(x, y, z);
        updateModel();
    }

    glm::vec3 getScale() const {
        return __scale;
    }


    glm::mat4 updateModel() {
        __model = glm::mat4(1);
        // __model = glm::rotate(__model, __angle, __rotation);
        __model = glm::translate(__model, __position);
        __model = glm::scale(__model, __scale);
        return __model;
    }

    glm::mat4 getPositionMatrix() const override {
        return __model;
    }

    glm::vec3 getPostionVector() const override {
        return __position;
    }

    ModelPosition operator+(const ModelPosition &position){
        glm::vec3 pos;
        glm::vec3 scale;


        pos = __position + position.__position;
        scale.x = __scale.x * position.__scale.x;
        scale.y = __scale.y * position.__scale.y;
        scale.z = __scale.z * position.__scale.z;
        
        ModelPosition n;
        n.__position = pos;
        n.__scale = scale;
        return n;
    }
};

}