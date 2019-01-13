#pragma once

#include <string>
#include <list>
#include <Engine/IUpdatable.hpp>
#include "../Entities/Entity.hpp"
#include "../Entities/Unit.hpp"

class Player : public IPlayer, public IDrawable, public Engine::Input::IUpdatable {
    std::list<Entity *> __selectedObjects;

    std::string __name;
    std::list<Entity *> __entities;
public:
    Player(const std::string &name): __name(name){}

    const std::string& getName() const { return __name; }

    void selectAllEntities(float x1, float z1, float x2, float z2) {
        float r1left = std::min(x1, x2);
        float r1right = std::max(x1, x2);
        float r1top = std::min(z1, z2);
        float r1bottom = std::max(z1, z2);
        __selectedObjects.clear();
        for (auto e: __entities) {
            if (e->getType() == Entity::Type::UNIT) {
                auto u = dynamic_cast<Unit *>(e);
                if (u->isInArea(r1left, r1top, r1right, r1bottom)) {
                    __selectedObjects.push_back(u);
                }
            }
        }

        auto logger = spdlog::get("log");
        logger->info("selected entities: {}", __selectedObjects.size());
    }

    void selectEntity(Entity *entity) {
        auto logger = spdlog::get("log");
        logger->info("entity selected {}", entity->getName());
        __selectedObjects.clear();
        __selectedObjects.push_back(entity);
    }

    void addEntity(Entity *__entity) {
        auto logger = spdlog::get("log");
        logger->info("new entity for player {}", __name);
        __entities.push_back(__entity);
    }

    void update(float delta_time) override {
        for (auto e: __entities) {
            e->update(delta_time);
        }
    }

    void moveTo(float x, float z) {
        auto logger = spdlog::get("log");
        logger->info("move to {} {}", x, z);

        for (auto e: __entities) {
            if (e->getType() == Entity::Type::UNIT) {
                auto u = dynamic_cast<Unit *>(e);
                u->setJob(new MoveToJob(glm::vec3(x, 0, z)));
            }
        }
    }

    void draw() const override {
        for (auto e: __entities) {
            e->draw();
        }
    }

    void attack(Entity *e) const {
        auto logger = spdlog::get("log");
        logger->info("attack entity {}", e->getName());
    }

};
