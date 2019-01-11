#pragma once

#include <Renders/OpenGL/Model.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/OpenGL/MeshWithBoundingBox.hpp>

class MeshesProvider{
    OpenGL::PositionShaderProgram *__program = nullptr;
    OpenGL::Model *__viper_model = nullptr;
    OpenGL::Model *__planet_model = nullptr;
public:
    MeshesProvider() {
        OpenGL::PositionShaderProgram *__program = new OpenGL::PositionShaderProgram();
        __program->loadShaders("./sharedAssets/shaders/useLightShader.vert",
         "./sharedAssets/shaders/useLightShader.frag");

//        __planet_model = new OpenGL::Model("./sharedAssets/planets/planet.obj");
//        __viper_model = new OpenGL::Model("./sharedAssets/models/viper/viper.obj");
    }

    OpenGL::Mesh* getPlanetMesh(float min_radius, float max_radius) {
        auto mesh = new OpenGL::MeshWithBoundingBox(__program, __planet_model);
        mesh->setScale(min_radius, min_radius, min_radius);
        return mesh;
    }

    OpenGL::Mesh* getSunMesh() {
        auto mesh = new OpenGL::MeshWithBoundingBox(__program, __planet_model);
        mesh->setScale(2.0f, 2.0f, 2.0f);
        return mesh;
    }

    OpenGL::Mesh* getViperMesh() {
        auto mesh = new OpenGL::MeshWithBoundingBox(__program, __planet_model);
        mesh->setScale(0.1f, 0.1f, 0.1f);
        return mesh;
    }
};
