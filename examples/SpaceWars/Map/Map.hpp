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

    OpenGL::AxiesDebug *__axiesDebug = nullptr;
    OpenGL::GridDebug *__gridDebug = nullptr;

    glm::vec3 planeN = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 planeP = glm::vec3(0.0f, 0.0f, 0.0f);

    StarsFactory *__starsFactory = nullptr;
    PlanetsFactory *__planetsFactory = nullptr;
    std::vector<Galaxy*> __galaxies;

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
        __axiesDebug = new OpenGL::AxiesDebug(__size, __size, __size);
        __axiesDebug->update();

        __gridDebug = new OpenGL::GridDebug(__size, __size, __size, 50);
        __gridDebug->update();
    }

    void draw() const override {
        glDisable(GL_DEPTH_TEST);
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
        glm::vec3 tmp = planeN * (-1.0f);
        auto d = glm::dot(planeP, tmp);
        if (std::abs(d) < 0.0001f) // your favorite epsilon
        {
            return {false, glm::vec3()};
        }

        auto rayP = ray.point1;
        auto rayD = ray.point2 - ray.point1;
        float t = -(d + rayP.z * planeN.z + rayP.y * planeN.y + rayP.x * planeN.x)
                / (rayD.z * planeN.z + rayD.y * planeN.y + rayD.x * planeN.x);

        if (t <= 0) {
            return {false, glm::vec3()};
        }

        auto ans = rayP + t * rayD;
        auto logger = spdlog::get("log");
        logger->info("ray intersect map at {} {} {}", ans.x, ans.y, ans.z);
        return {true, glm::vec3(ans.x, ans.y, ans.z)};
    }

    bool enableDebug() {
        __debug = true;
    }

    bool disableDebug() {
        __debug = false;
    }
};
