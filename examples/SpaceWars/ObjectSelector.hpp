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
    std::function<void(Entity *entity)> __listener;
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
//        __target = new OpenGL::VectorDebug(0, 0, 0, 0, 0, 0, glm::vec3(1.0f, 1.0f, 0.0f));

        glEnable(GL_DEPTH_TEST);
        auto starModel = new OpenGL::Model("./sharedAssets/models/sol/sol.obj", __program);
        __mesh = new OpenGL::Mesh(__program, starModel);
        __mesh->setScale(0.2, 0.2f, 0.2f);
        __callback = new RaycastCallback(__mesh);
    }

    void processKey(Engine::Input::Key key) override {
        updateDebugData();
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
//        __target->draw();
        glEnable(GL_DEPTH_TEST);
    }

    void onMouseMove(float x, float y, float dx, float dy) override {
        __x = x;
        __y = y;
        updateDebugData();
    }

    void onMouseUp(Engine::Input::MouseButton key, float x, float y, int mods) override {

    };

    bool onMouseDown(Engine::Input::MouseButton key, float x, float y, int mods) override {
        auto ray = __camera->castRay(__x, __y, __width, __height);
        __callback->refresh();
        __world->raycast(ray, __callback);

        if (__callback->wasHit()) {
            auto e = __callback->getSelectedEntity();
            if (__player != e->getPlayer() && key == Engine::Input::MouseButton::RIGHT){
                __player->attack(e);
            }

            if (key == Engine::Input::MouseButton::LEFT) {
                __listener(e);
            }
            return true;
        }

        return false;
    };

    void updateDebugData() {
        auto ray = __camera->castRay(__x, __y, __width, __height);

        auto f = 10.0f * __camera->getForwardVector();
        auto r = 10.0f * __camera->getRightVector();
        auto u = 10.0f * __camera->getUpVector();

        auto p = __camera->getPosition();

        __center->update(0, 0, 0, c.x, c.y, c.z);
        __up->update(c.x + u.x, c.y + u.y, c.z + u.z, c.x, c.y, c.z);
        __right->update(c.x + r.x, c.y + r.y, c.z + r.z, c.x, c.y, c.z);
        __forward->update(c.x + f.x, c.y + f.y, c.z + f.z, c.x, c.y, c.z);

//        __target->update(ray.point1.x, ray.point1.y , ray.point1.z , ray.point2.x, ray.point2.y, ray.point2.z);
    }

    void setListener(std::function<void(Entity *entity)> func) {
        __listener = func;
    }
};