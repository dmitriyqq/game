#pragma once

#include "../../MyGame/include/IVoxelRenderingBackend.hpp"
#include <Renders/IDrawable.hpp>

#include <deque>
#include <array>
#include <Engine/IKeyboardSubscriber.hpp>
#include "../../MyGame/include/Voxel.hpp"

class Snake : public IDrawable, public Engine::Input::IKeyboardSubscriber{
    int __x = 1, __y = 1;
    int __length = 3;
    enum class Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3} __direction = Direction::EAST;

    std::deque<std::pair<int, int> > __segments;

public:
    bool collide(int x, int y){
        return (x == __x && y == __y);
    }

    void processKey(Engine::Input::Key key) override {
        using keyType = Engine::Input::Key;
        switch (key){
            case keyType::UP: if(__direction != Direction::SOUTH) __direction = Direction::NORTH; break;
            case keyType::LEFT: if(__direction != Direction::EAST) __direction = Direction::WEST; break;
            case keyType::DOWN: if(__direction != Direction::NORTH) __direction = Direction::SOUTH; break;
            case keyType::RIGHT: if(__direction != Direction::WEST) __direction = Direction::EAST; break;
            default: break;
        }
    }

    void draw(IVoxelRenderingBackend * backend) const override{
        Voxel voxel;
        voxel.type = Voxel::Type::WATER;
        for(auto &&s: __segments){
            backend->display(voxel, s.second, s.first);
        }
    }

    void move(){
        using velocity = std::pair<int, int>;
        std::array<velocity,4> VELOCITIES = {
                velocity(0, -1),
                velocity(1, 0),
                velocity(0, 1),
                velocity(-1, 0),
        };

        int dX = VELOCITIES[(int)__direction].first;
        int dY = VELOCITIES[(int)__direction].second;
        int newX = __x + dX;
        int newY = __y + dY;

        __segments.emplace_back(newX, newY);
        __x = newX;
        __y = newY;

        if((int)__segments.size() > __length) {
            __segments.pop_front();
        }
    }

    void grow(){
        this->__length++;
    }
};
