#pragma once

#include <Engine/IMouseSubscriber.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/OpenGL/Geometry/RectangleXZ.hpp>
#include <Renders/IDrawable.hpp>
#include "Players/Player.hpp"

class MapSelector: public Engine::Input::IMouseSubscriber, public IDrawable {
    Player *__player = nullptr;
    Map * __map;
    OpenGL::PositionShaderProgram *__program = nullptr;
    OpenGL::RectangleXZ *__rect = nullptr;

    OpenGL::ICamera *__camera = nullptr;

    bool __draw = false;
    float __x1, __y1, __x2, __y2;
    float __width, __height;
public:
    MapSelector(Map* map, Player *player, OpenGL::PositionShaderProgram *debugProgam, OpenGL::ICamera *camera, float width, float height):
    __player(player), __program(debugProgam), __camera(camera), __width(width), __height(height), __map(map) {
        __rect = new OpenGL::RectangleXZ(0, 0, 0, 0);
    }

    std::pair<float, float> screenToMap(float x, float y){
        auto ray = __camera->castRay(x, y, __width, __height);
        auto p = __map->getIntersectionPoint(ray);

        return {p.second.x, p.second.z};
    };

    void onMouseMove(float x, float y, float dx, float dy) override {
        auto p = screenToMap(x, y);
        __x2 = p.first;
        __y2 = p.second;

        if (__draw) {
            updateRect();
        }
    }

    void onMouseUp(Engine::Input::MouseButton key, float x, float y, int mods) override {
        auto p = screenToMap(x, y);
        __x2 = p.first;
        __y2 = p.second;

        float dx = std::abs(__x1 - __x2);
        float dy = std::abs(__x2 - __x2);

        if (dx > 3.0f && dy > 3.0f) {
            if (key == Engine::Input::MouseButton::LEFT) {
                __player->selectAllEntities(__x1, __y1, __x2, __y2);
            }
        } else {
            if (key == Engine::Input::MouseButton::RIGHT) {
                __player->moveTo(__x2, __y2);
            }
        }
        __draw = false;

        updateRect();

    };

    void updateRect() {
        __rect->update(__x1, __y1, __x2, __y2);
    }

    bool onMouseDown(Engine::Input::MouseButton key, float x, float y, int mods) override {

            auto p = screenToMap(x, y);
            __x2 = __x1 = p.first;
            __y2 = __y1 = p.second;
            updateRect();
            __draw = true;

        return false;
    };

    void draw() const override {
        if( __draw) {
            __program->use();
            __rect->draw();
        }
    }

    glm::vec3 getSelectedPoint() {
        return glm::vec3(__x2, 0.0f, __y2);
    }
};
