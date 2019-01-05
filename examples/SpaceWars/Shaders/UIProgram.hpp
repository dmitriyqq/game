#pragma once

#include <Renders/OpenGL/ShaderProgram.hpp>

class UIProgram : OpenGL::ShaderProgram {
    public:
    UIProgram() {
        loadShaders("sharedAssets/shaders/model.vert", "sharedAssets/shaders/model.frag");
    }
};
