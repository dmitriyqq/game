#pragma once

#include <Renders/OpenGL/Model.hpp>

#include <reactphysics3d.h>
#include <random>

#include "Entities/Star.hpp"

class Player;

class StarsFactory {
    OpenGL::Model *__model = nullptr;
    rp3d::DynamicsWorld *__world = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;
    Texture *__texture = nullptr;
    std::uniform_real_distribution<> __dist;
    std::mt19937 __rnd;

public:
    StarsFactory(OpenGL::Model *model,
                 rp3d::DynamicsWorld *world,
                 OpenGL::PositionShaderProgram *program,
                 Texture *texture):
        __model(model),
        __world(world),
        __program(program),
        __dist(5, 10),
        __texture(texture)
    {
    }

    Star* createStar(Player *player, glm::vec3 position) {
        float t = static_cast<float>(__dist(__rnd));
        Star *star = new Star(__model, __program, __world, position, t);
        star->setPlayer(player);
        star->setIcon(__texture);
        return star;
    }
};
