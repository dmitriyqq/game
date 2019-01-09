#pragma once

#include <Engine/IMouseSubscriber.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/IDrawable.hpp>
#include <Renders/OpenGL/Geometry/AxiesDebug.hpp>
#include <Renders/OpenGL/Geometry/GridDebug.hpp>

#include <reactphysics3d.h>
#include <glm/glm.hpp>

#include "../Entities/Galaxy.hpp"

class Map : Engine::Input::IMouseSubscriber, IDrawable {
    bool __debug = false;
    float __size;
    rp3d::CollisionBody *body = nullptr;

    OpenGL::PositionShaderProgram *program = nullptr;
    OpenGL::PositionShaderProgram *debugProgram = nullptr;

    OpenGL::AxiesDebug *__axiesDebug = nullptr;
    OpenGL::GridDebug *__gridDebug = nullptr;

    glm::vec3 planeN = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 planeP = glm::vec3(0.0f, 0.0f, 0.0f);

    std::vector<Galaxy*> __galaxies;
public:
    Map(OpenGL::PositionShaderProgram *program, OpenGL::PositionShaderProgram *debugProgram, float size = 1024.0f):
        __size(size) {
        __axiesDebug = new OpenGL::AxiesDebug(__size, __size, __size);
        __axiesDebug->update();

        __gridDebug = new OpenGL::GridDebug(__size, __size, __size, 50);
        __gridDebug->update();
    }

    void draw() const {
        if(__debug) {
            debugProgram->use();
            __axiesDebug->draw();
            __gridDebug->draw();
        }
        program->use();
        for (auto galaxy: __galaxies) {
            galaxy->draw();
        }
    }

    std::pair<bool, glm::vec3> getIntersectionPoint(rp3d::Ray ray) {
        auto d = glm::dot(planeP, -planeN);
        if (std::abs(d) < 0.0001f) // your favorite epsilon
        {
            return {false, glm::vec3()};
        }

        auto rayP = ray.point1;
        auto rayD = ray.point2 - ray.point1;
        float t = -(d + rayP.z * planeN.z + rayP.y * planeN.y + rayP.x * planeN.x) / (rayD.z * planeN.z + rayD.y * planeN.y + rayD.x * planeN.x);

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
