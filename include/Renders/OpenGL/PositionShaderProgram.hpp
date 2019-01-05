#pragma once

#include<Renders/OpenGL/ShaderProgram.hpp>

namespace OpenGL{

class PositionShaderProgram: public OpenGL::ShaderProgram {
    public: 
    PositionShaderProgram(glm::mat4 model = glm::mat4(1)) {
        setMat4("model", model);
    }

    void setModel(glm::mat4 model) {
        setMat4("model", model);
    }
};

}