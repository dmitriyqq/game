#pragma once

#include "Players/Player.hpp"
#include "ArcBallCamera.hpp"
#include "RaycastCallback.hpp"
#include "Map/Map.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Renders/OpenGL/Geometry/Cube.hpp>
#include <Renders/OpenGL/Geometry/VectorDebug.hpp>

class ObjectSelector: public Engine::Input::IMouseSubscriber, public Engine::Input::IKeyboardSubscriber  {
    Player *__player = nullptr;
    Map *__map = nullptr;

    float __x = 0, __y = 0;
    float __width, __height;

    bool __debug = false;

    rp3d::DynamicsWorld *__world = nullptr;
    RaycastCallback *__callback = nullptr;
    OpenGL::Mesh *__mesh = nullptr;
    OpenGL::ICamera *__camera = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;
    OpenGL::PositionShaderProgram *__debugProgram = nullptr;

    OpenGL::VectorDebug *__center = nullptr;
    OpenGL::VectorDebug *__up = nullptr;
    OpenGL::VectorDebug *__right = nullptr;
    OpenGL::VectorDebug *__forward = nullptr;
    OpenGL::VectorDebug *__target = nullptr;

    glm::vec3 c = glm::vec3(0.0f, 0.0f, 0.0f);

public:
    ObjectSelector(
            Map *map,
            bool debug,
            rp3d::DynamicsWorld *world,
            OpenGL::ICamera *camera,
            OpenGL::PositionShaderProgram *debugProgram,
            OpenGL::PositionShaderProgram *program,
            Player *player,
            float width,
            float height):
            __player(player),
            __map(map),
            __width(width),
            __height(height),
            __debug(debug),
            __world(world),
            __camera(camera),
            __program(program),
            __debugProgram(debugProgram)
    {
        __center = new OpenGL::VectorDebug(0, 0, 0, 0, 0, 0, glm::vec3(1.0f, 0.0f, 1.0f));
        __up = new OpenGL::VectorDebug(0, 0, 0, 0, 0, 0, glm::vec3(1.0f, 0.0f, 0.0f));
        __right = new OpenGL::VectorDebug(0, 0, 0, 0, 0, 0, glm::vec3(0.0f, 0.0f, 1.0f));
        __forward = new OpenGL::VectorDebug(0, 0, 0, 0, 0, 0, glm::vec3(0.0f, 1.0f, 0.0f));
        __target = new OpenGL::VectorDebug(0, 0, 0, 0, 0, 0, glm::vec3(1.0f, 1.0f, 0.0f));

        auto cube = new OpenGL::Cube();
        cube->update();
        __mesh = new OpenGL::Mesh(__program, cube);
        __callback = new RaycastCallback(__mesh);
    }

    void processKey(Engine::Input::Key key) override {
        updateData();
    }

    void draw(){
        glDisable(GL_DEPTH_TEST);
        __program->use();
        __callback->draw();
        __debugProgram->use();
        __center->draw();
        __up->draw();
        __right->draw();
        __forward->draw();
        __target->draw();
        glEnable(GL_DEPTH_TEST);
    }

    void update(double x, double y, double dx, double dy) override {
        __x = static_cast<float>(x);
        __y = static_cast<float>(y);
        updateData();
    }

    void onMouseUp(Engine::Input::MouseButton key) override {};

    void onMouseDown(Engine::Input::MouseButton key) override {};

    void updateData(){

        float x = (2.0f * __x) / __width - 1.0f;
        float y = 1.0f - (2.0f * __y) / __height;
        float z = 1.0f;

        glm::vec3 ray_nds =  glm::vec3(x, y, z);
        glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
        glm::vec4 ray_eye =  glm::inverse(__camera->getProjectionMatrix(__width, __height)) * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
        glm::vec3 ray_wor = glm::inverse(__camera->getViewMatrix()) * ray_eye;

        ray_wor = glm::normalize(ray_wor);

        auto f = 10.0f * __camera->getForwardVector();

        auto r = 10.0f * __camera->getRightVector();
        auto u = 10.0f * __camera->getUpVector();
        auto o = y * u / 10.0f + x * r / 10.0f;

        auto p = __camera->getPosition();

        __center->update(0, 0, 0, c.x, c.y, c.z);
        __up->update(c.x + u.x, c.y + u.y, c.z + u.z, c.x, c.y, c.z);
        __right->update(c.x + r.x, c.y + r.y, c.z + r.z, c.x, c.y, c.z);
        __forward->update(c.x + f.x, c.y + f.y, c.z + f.z, c.x, c.y, c.z);

        auto ff = __camera->getForwardVector();
        rp3d::Vector3 start(p.x + o.x, p.y + o.y, p.z + o.z);
        rp3d::Vector3 end(p.x + o.x + 1000.0f * ray_wor.x, p.y + o.y + 1000.0f * ray_wor.y, p.z + o.z + 1000.0f * ray_wor.z);
        rp3d::Ray ray(start, end);
        __target->update(start.x, start.y , start.z , end.x, end.y, end.z);

        __callback->refresh();
        __world->raycast(ray, __callback);

        if (!__callback->wasHit()) {
            auto log = spdlog::get("log");
            log->info("ray doesn't intersect any object");
            __map->getIntersectionPoint(ray);
        }

    }
};