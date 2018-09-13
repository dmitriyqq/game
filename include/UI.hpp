#pragma once

#include "Camera.hpp"
#include "DebugWindow.hpp"

class UI {

    Camera *camera;
    DebugWindow *window;

public:
    UI(){
        camera = new Camera();
        window = new DebugWindow(DebugWindow::getXOffset(camera->width()), camera->height());
    }

    void debug(const std::string &key, std::string &value){
        window->debug(key, value);
    }

    void debug(const std::string &key, int value){
        window->debug(key, std::to_string(value));
    }

    void debug(const std::string &key, double value){
        window->debug(key, std::to_string(value));
    }

    void display(const ISpace *space){

        debug("width", camera->width());
        debug("height", camera->height());

        camera->display(space);
        window->draw();
    }
};
