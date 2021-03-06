#pragma once

#include <random>
#include <Renders/OpenGL/Model.hpp>
#include "Entities/Planet.hpp"
#include "Players/Player.hpp"

class PlanetsFactory {
    OpenGL::Model *__model = nullptr;
    rp3d::DynamicsWorld *__world = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;
    Texture *__texture;
    std::uniform_real_distribution<float> __dist;
    std::mt19937 __rnd;
public:
    PlanetsFactory(OpenGL::Model *model,
            rp3d::DynamicsWorld *world,
            OpenGL::PositionShaderProgram *program, Texture *texture):
            __model(model),
            __world(world),
            __program(program),
            __dist(1, 2.5f),
            __texture(texture)
    {
    }

    Planet* createPlanet(Player *player, glm::vec3 center, float orbitRadius) {
        float t = __dist(__rnd);
        Planet *planet = new Planet(__model, __program, __world, center, t, orbitRadius, 2.0f *(__dist(__rnd) - 1.0f), 0.05f * __dist(__rnd));
        planet->setPlayer(player);
        planet->setIcon(__texture);
        return planet;
    }
};

