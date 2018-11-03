#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renders/OpenGL/ShaderProgram.hpp"

using glm::vec3;
using OpenGL::ShaderProgram;

class DirectLight {
    vec3 m_direction;
    vec3 m_ambient;
    vec3 m_diffuse;
    vec3 m_specular;

public:
    explicit DirectLight(
                vec3 direction = vec3(0.0f, 1.0f, 0.0f),
                vec3 ambient = vec3(0.5f, 0.5f, 0.5f),
                vec3 diffuse = vec3(0.4f, 0.4f, 0.4f),
                vec3 specular = vec3(1.0f, 1.0f, 1.0f)
                ) :
            m_direction(direction),
            m_ambient(ambient),
            m_diffuse(diffuse),
            m_specular(specular)
    {
    }

    void uniform(ShaderProgram * program){
        program->setVec3("dirLight.direction", m_direction);
        program->setVec3("dirLight.ambient", m_ambient);
        program->setVec3("dirLight.diffuse", m_diffuse);
        program->setVec3("dirLight.specular", m_specular);
    }

    virtual ~DirectLight() = default;
};

#endif // DIRECTLIGHT_H
