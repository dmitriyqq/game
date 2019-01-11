#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d.h>
#include <Renders/OpenGL/Model.hpp>

#include "../PlanetsFactory.hpp"
#include "../StarsFactory.hpp"
#include "Planet.hpp"

class Galaxy: public Entity{
    static constexpr int NUM_PLANETS = 5;

    StarsFactory *__starFactory = nullptr;
    PlanetsFactory *__planetsFactory = nullptr;

    Star *__star = nullptr;
    std::vector <Planet *> __planets;

public:
    Galaxy(StarsFactory* starsFactory,
           PlanetsFactory* planetsFactory,
           Player* player,
           glm::vec3 position):
        __starFactory(starsFactory),
        __planetsFactory(planetsFactory), Entity(player) {
        __star = __starFactory->createStar(player, position);

        float step = 8.0f;
        float offset = __star->getRadius() + 2.0f * step;
        for (int i = 0; i < NUM_PLANETS; i++) {
            auto planet = __planetsFactory->createPlanet(player, position, offset);
            offset += 4.0f * planet->getRadius() + step;
            __planets.push_back(planet);
        }
    }

    void draw() const override {
        __star->draw();

        for(auto &&planet: __planets) {
            planet->draw();
        }
    }

    void update(float delta_time) override {
        for(auto &&planet: __planets) {
            planet->update(delta_time);
        }
    }
};