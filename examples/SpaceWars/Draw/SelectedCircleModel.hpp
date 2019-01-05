#pragma once

#include "../Model.hpp"
#include <Render/OpenGL/IProgram>

class PlanetModel: public Model {
    public:
        PlanetModel(OpenGL::IProgram *program): Model("./sharedAssets/models/selected.obj", program) {}
};
