#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d.h>
#include <Renders/OpenGL/Model.hpp>

#include "../PlanetsFactory.hpp"
#include "../StarsFactory.hpp"
#include "Planet.hpp"

class Galaxy: Entity{
    static constexpr int NUM_PLANETS = 5;

    StarsFactory *__starFactory = nullptr;
    PlanetsFactory *__planetsFactory = nullptr;

    Star *__star = nullptr;
    std::vector <Planet *> __planet;

public:
    Galaxy(StarsFactory* starsFactory,
           PlanetsFactory* planetsFactory,
           Player* player,
           glm::vec3 position):
        __starFactory(starsFactory),
        __planetsFactory(planetsFactory,
        Entity(player)
   {
        __star = __starFactory->createStar();
        for(int i = 0; i < NUM_PLANETS; i++) {
            rp3d::RigidBody *body = world.createRigidBody(rp3d::Transform::identity());
            // __planets[i] = new Planet(model, program, body, );
        }
    }
    // Galaxy(glm::vec3 position): Planet() {
    //     // __sun = new Sun()
    // }
};