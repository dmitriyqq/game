#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/IDrawable.hpp>

#include "reactphysics3d.h"

class RaycastCallback : public rp3d::RaycastCallback, public IDrawable{
    OpenGL::Mesh *__mesh = nullptr;
    nanogui::Window *__window = nullptr;
    Entity *__selectedEntity = nullptr;

    bool __hit = false;
    virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) override {

        auto logger = spdlog::get("log");
        logger->info("Hit point : {} {} {}", info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);

        auto hit = info.body->getUserData();

        __selectedEntity = static_cast<Entity*> (info.body->getUserData());
        __mesh->setPosition(info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);
        __hit = true;
        return rp3d::decimal(0.0);
    }

public:
    RaycastCallback(OpenGL::Mesh *mesh): __mesh(mesh) {}

    void draw() const override {
        __mesh->draw();
    }

    bool wasHit() {
        return __hit;
    }

    void refresh() {
      __hit = false;
    }

    Entity *getSelectedEntity() {
        return __selectedEntity;
    }
};