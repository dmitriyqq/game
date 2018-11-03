#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renders/OpenGL/ShaderProgram.hpp"

using glm::vec3;
using OpenGL::ShaderProgram;

class PointLight {
    static constexpr float CONSTANT = 1.0f;
    static constexpr float LINEAR = 0.1f;
    static constexpr float QUADRATIC = 0.22f;
    static int count;

    int __id;
    vec3 __position;

    float __constant;
    float __linear;
    float __quadratic;

    vec3 __ambient;
    vec3 __diffuse;
    vec3 __specular;

public:
    explicit PointLight(
        vec3 position = vec3(0.0f, 0.0f, 0.0f),
        vec3 ambient = vec3(0.1f, 0.1f, 0.1f),
        vec3 diffuse = vec3(0.5f, 0.5f, 0.5f),
        vec3 specular = vec3(1.0f, 1.0f, 1.0f)):
    __position(position),
    __constant(CONSTANT),
    __linear(LINEAR),
    __quadratic(QUADRATIC),
    __ambient(ambient),
    __diffuse(diffuse),
    __specular(specular)
    {
        __id = count;
        count++;
    }

    virtual ~PointLight() = default;

    void uniform(ShaderProgram * program){
        using std::to_string;
        program->setFloat("pointLights["+to_string(__id)+"].__constant", __constant);
        program->setFloat("pointLights["+to_string(__id)+"].__linear", __linear);
        program->setFloat("pointLights["+to_string(__id)+"].__quadratic", __quadratic);
        program->setVec3("pointLights["+to_string(__id)+"].position", __position);
        program->setVec3("pointLights["+to_string(__id)+"].ambient", __ambient);
        program->setVec3("pointLights["+to_string(__id)+"].diffuse", __diffuse);
        program->setVec3("pointLights["+to_string(__id)+"].specular", __specular);
    }

    void setPosition(vec3 position, ShaderProgram * program){
        __position = position;
        program->setVec3("pointLights["+std::to_string(__id)+"].position", __position);
    }

    vec3 getPosition() const { return __position; }

    void setDiffuse(vec3 diffuse, ShaderProgram * program){
        __diffuse = diffuse;
        program->setVec3("pointLights["+std::to_string(__id)+"].diffuse", __diffuse);
    }

    vec3 getDiffuse() const { return __diffuse; }
};

int PointLight::count = 0;
