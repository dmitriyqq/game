#pragma once

#include "../Model.hpp"
#include <Renders/OpenGL/IProgram.hpp>

class PlanetModel: public Model {
    public:
        PlanetModel(OpenGL::IProgram *program): Model("./sharedAssets/planets/planet.obj", program) {}
};
