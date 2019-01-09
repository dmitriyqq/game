#pragma once

#include <nanogui/nanogui.h>
#include <Renders/OpenGL/ICamera.hpp>
#include "Vector.hpp"

class DebugCamera: public nanogui::Window {
    Vector *__position;
    Vector *__forward;
    OpenGL::ICamera *__camera = nullptr;
public:
    DebugCamera(nanogui::Screen *screen, OpenGL::ICamera *camera):
        nanogui::Window(screen, ""),
        __camera(camera) {
        setPosition(nanogui::Vector2i(0, 0));
        setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum));

        __position = new Vector(this);
        addChild(__position);

        __forward = new Vector(this);
        addChild(__forward);
        update();
    }

    void update() {
        auto p = __camera->getPosition();
        __position->setValue(p);
        auto f = __camera->getForwardVector();
        __forward->setValue(f);
    }
};
