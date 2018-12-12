#pragma once

#include "SnakeBonus.hpp"

class Wall : public SnakeBonus{
public:
    Wall(int x, int y): SnakeBonus(x, y){};
    std::pair<bool, bool> isEaten(Snake &snake) override{
        if(snake.collide(__x, __y)){
            return {true, true};
        }else{
            return {false, false};
        }
    }
    void draw(IWindow *window) const override{
        Voxel voxel;
        voxel.type = Voxel::Type::SAND;
        // backend->display(voxel, __y, __x);
    }
};

