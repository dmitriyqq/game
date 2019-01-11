#pragma once

#include <nanogui/nanogui.h>
#include <Renders/OpenGL/ICamera.hpp>
#include "Vector.hpp"

class DebugCamera {
    VectorWidget *__position;
    VectorWidget *__forward;
    OpenGL::ICamera *__camera = nullptr;
    nanogui::Window *__window = nullptr;
public:
    DebugCamera(nanogui::Screen *screen, OpenGL::ICamera *camera):
        __camera(camera) {
        __window = new nanogui::Window(screen);
        __window->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum, 0, 0));
        __position = new VectorWidget(__window);
        __window->addChild(__position);
        __forward = new VectorWidget(__window);
        __window->addChild(__forward);
        update();
    }

    void update() {
        auto p = __camera->getPosition();
        __position->setValue(p);
        auto f = __camera->getForwardVector();
        __forward->setValue(f);
    }

    nanogui::Window* getWindow() {
        return __window;
    }
};
