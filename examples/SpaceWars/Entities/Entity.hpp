#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/IBoundingBoxDrawable.hpp>
#include <Renders/OpenGL/BoundingBox.hpp>
#include <Renders/OpenGL/Graphics2D.hpp>
#include <Engine/ISelectable.hpp>
#include <Renders/OpenGL/Utils.hpp>
#include <IEntity.hpp>

#include <vector>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <reactphysics3d.h>
#include <nanogui/nanogui.h>
#include "../UI/EntityWindow.hpp"
#include "IPlayersEntity.hpp"

class StarsFactory;
class PlanetsFactory;
class Player;

class Entity : public Engine::IEntity, public IPlayersEntity {
    Player* __player = nullptr;
    nanogui::Window *__window = nullptr;
    Texture *__texture = nullptr;
protected:
    void setPlayer(Player* player){ __player = player;}
public:
    float health;
    float armor;

    enum class Type {
        ENTITY, PLANET, STAR, ASTEROID, UNIT, GALAXY
    };

    Entity(Player *player = nullptr): __player(player) {}

    Player* getPlayer() const { return __player;}

    virtual void update(float delta_time){
        auto log = spdlog::get("log");
        log->error("Calling update on static entity. This is strange");
    };

    void setIcon(Texture *texture) {
        __texture = texture;
    }

    virtual void draw() const {
        auto log = spdlog::get("log");
        log->error("Calling draw on headless entity. This is strange");
    }

    virtual nanogui::Window* getWindow() {
        if (__window == nullptr) {
            __window = new EntityWindow(nullptr, getName(), getPlayer()->getName(), health, armor, __texture->getId());
        }

        return __window;
    }

    virtual Type getType() {
        return Type::ENTITY;
    }

    virtual const char* getName() {
        return "Entity";
    }
};