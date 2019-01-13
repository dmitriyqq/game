#pragma once

#include "Entities/Unit.hpp"
#include "Meta/UnitMetaInfo.hpp"
#include "Players/Player.hpp"
#include "Entities/Viper.hpp"

class UnitsFactory {
public:
    std::vector <UnitMetaInfo *> __units;
    rp3d::DynamicsWorld *__world = nullptr;
    OpenGL::PositionShaderProgram *__program = nullptr;

    UnitsFactory(rp3d::DynamicsWorld *world,
                 OpenGL::PositionShaderProgram *program):
    __world(world),
    __program(program){
        __units.push_back(new UnitMetaInfo("viper",
                                           "./sharedAssets/models/viper/viper.obj",
                                           "./sharedAssets/icons/units/viper.png",
                                           __program, glm::vec3(0.1f,0.1f, 0.1f)));
        __units.push_back(new UnitMetaInfo("trident", "./sharedAssets/models/trident/trident3.obj",
                                           "./sharedAssets/icons/units/trident.png",
                                           __program, glm::vec3(1.0f,1.0f, 1.0f)));
//        __units.push_back(new UnitMetaInfo("spaceship", "./sharedAssets/models/mosquito/mosquito.obj",
//                                           "./sharedAssets/icons/units/spaceship.png",
//                                           __program,  glm::vec3(1.01f,1.01f, 1.01f)));
    }

    const std::vector <UnitMetaInfo *>& getAvailableUnits() {
        return __units;
    }

    Unit* constructUnit(UnitMetaInfo * info, Player *player) {
        auto v = new Unit(__program, info->model, info->scale, info->name);
        v->setIcon(info->texture);
        v->setPlayer(player);
        v->addToWorld(__world, glm::vec3(0,0,0));
        return v;
    }
};

