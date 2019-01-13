#pragma once

#include <string>
#include <Renders/OpenGL/Model.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>

// BASICALLY DATA STORAGE FOR UNITS FACTORY

struct UnitMetaInfo {
    std::string name;
    std::string modelPath;
    std::string imagePath;
    glm::vec3 scale;

    OpenGL::Model *model = nullptr;
    Texture *texture = nullptr;
    UnitMetaInfo(const std::string name, std::string modelPath, std::string imagePath, OpenGL::PositionShaderProgram *program, glm::vec3 scale):
        name(name), modelPath(modelPath), imagePath(imagePath), scale(scale)
    {
        model = new OpenGL::Model(modelPath, program);
        texture = new Texture(imagePath);
    }
};

