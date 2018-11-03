#pragma once

#include <Renders/IDrawable.hpp>
#include "Snake.hpp"

class SnakeBonus : public IDrawable{
protected:
    int __x = 0, __y = 0;

public:
    SnakeBonus(int x, int y): __x(x), __y(y){
    }

    virtual std::pair<bool, bool> isEaten(Snake &snake){
        if(snake.collide(__x, __y)){
            snake.grow();
            return {true, false};
        }else{
            return {false, false};
        }

    }

    void draw(IVoxelRenderingBackend * backend) const override{
        Voxel voxel;
        voxel.type = Voxel::Type::GRASS;
        backend->display(voxel, __y, __x);
    }

    void recreate(int newX, int newY){
        __x = newX;
        __y = newY;
    }
};
