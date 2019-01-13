#pragma once

#include <Engine/IMouseSubscriber.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/IDrawable.hpp>
#include <Renders/OpenGL/Geometry/AxiesDebug.hpp>
#include <Renders/OpenGL/Geometry/GridDebug.hpp>

#include <reactphysics3d.h>
#include <glm/glm.hpp>

#include "../Entities/Galaxy.hpp"

class Map : IDrawable, Engine::Input::IUpdatable {
    bool __debug = true;
    float __size;

    OpenGL::PositionShaderProgram *__program = nullptr;
    OpenGL::PositionShaderProgram *__debugProgram = nullptr;
    OpenGL::Mesh *__skyBox = nullptr;
    OpenGL::AxiesDebug *__axiesDebug = nullptr;
    OpenGL::GridDebug *__gridDebug = nullptr;

    glm::vec3 planeN = glm::vec3(0.0f, 1.0f, 0.0f);


    StarsFactory *__starsFactory = nullptr;
    PlanetsFactory *__planetsFactory = nullptr;
    std::vector<Galaxy*> __galaxies;

    rp3d::BoxShape *__shape;
    rp3d::CollisionBody *__body;
    rp3d::CollisionWorld *__world;

public:

    Map(OpenGL::PositionShaderProgram *program,
        OpenGL::PositionShaderProgram *debugProgram,
        StarsFactory *starsFactory,
        PlanetsFactory *planetsFactory, float size = 1024.0f):
        __program(program),
        __debugProgram(debugProgram),
        __starsFactory(starsFactory),
        __planetsFactory(planetsFactory),
        __size(size) {

        __world = new rp3d::CollisionWorld();
        __shape = new rp3d::BoxShape(rp3d::Vector3(size / 2.0f, 0.5f, size /2.0f));
        __body = new rp3d::CollisionBody(rp3d::Transform::identity(), *__world, 1);
        __body->addCollisionShape(__shape, rp3d::Transform::identity());

        __axiesDebug = new OpenGL::AxiesDebug(__size, __size, __size);
        __axiesDebug->update();

        __gridDebug = new OpenGL::GridDebug(__size, __size, __size, 50);
        __gridDebug->update();

        auto model = new OpenGL::Model("./sharedAssets/models/sky/sky.obj", __program);
        __skyBox = new OpenGL::Mesh(__program, model);
        __skyBox->setScale(size/2.0f, size/2.0f, size/2.0f);
    }

    void draw() const override {
        glDisable(GL_DEPTH_TEST);
        __skyBox->draw();
        if(__debug) {
            __debugProgram->use();
            __axiesDebug->draw();
            __gridDebug->draw();
        }
        __program->use();
        glEnable(GL_DEPTH_TEST);
        for (auto galaxy: __galaxies) {
            galaxy->draw();
        }
    }

    void update(float delta_time) override {
        for(auto &&galaxy: __galaxies) {
            galaxy->update(delta_time);
        }
    }

    void constructGalaxy(glm::vec3 position, Player *player) {
        __galaxies.emplace_back(new Galaxy(__starsFactory, __planetsFactory, player, position));
    }

    std::pair<bool, glm::vec3> getIntersectionPoint(rp3d::Ray ray) {
        rp3d::RaycastInfo info;
        __body->raycast(ray, info);
        return {true, glm::vec3(info.worldPoint.x, 0, info.worldPoint.z)};
    }

    bool enableDebug() {
        __debug = true;
    }

    bool disableDebug() {
        __debug = false;
    }
};
