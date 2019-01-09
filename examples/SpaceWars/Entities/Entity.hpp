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

class StarsFactory;
class PlanetsFactory;
class Player;

class Entity : public Engine::IEntity {

    Player* __player = nullptr;
protected:
    void setPlayer(Player* player){ __player = player;}
public:
    Entity(Player *player = nullptr): __player(player) {}

    Player* getPlayer() const { return __player;}

    virtual void update(float delta_time){
        auto log = spdlog::get("log");
        log->error("Calling update on static entity. This is strange");
    };

    virtual void draw() const {
        auto log = spdlog::get("log");
        log->error("Calling draw on headless entity. This is strange");
    }
};