#include <iostream>
#include "Camera.hpp"
#include "VoxelSpace.hpp"


template< typename SpaceT, typename CameraT >
class Game{
    SpaceT _space;
    CameraT _camera;

public:
    Game(){
        _space.generate(100, 100, 100);
    }

    template <typename SpaceT, typename CameraT>
    void update(){
        std::cout<<"update"<<std::endl;
    }

    template <typename SpaceT, typename CameraT>
    void draw(){
        _camera.display(_space);
    }

};

int main(int argc, char** argv){
    auto myGame = new Game<SimpleSpace, Camera>();
    myGame.draw();
    
}