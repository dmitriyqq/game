#pragma once

#include <glm/glm.hpp>

struct Material{
    float shininess;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Material():
    shininess(0.5),
    diffuse(0.5, 0.5, 0.5),
    specular(0.5, 0.5, 0.5){

    }
};

struct TexutureMaterial: Material{
    
};