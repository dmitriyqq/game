#pragma once

#include <nanogui/nanogui.h>
#include <glm/glm.hpp>
#include <string>

class Vector : public nanogui::Widget {
    nanogui::Label *__x, *__y, *__z;
public:
    Vector(nanogui::Widget *parent): nanogui::Widget(parent) {
        setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Minimum));
        __x = new nanogui::Label(this, "");
        __y = new nanogui::Label(this, "");
        __z = new nanogui::Label(this, "");
        addChild(__x);
        addChild(__y);
        addChild(__z);
    }

    void setValue(glm::vec3 v) {
        setValue(v.x, v.y, v.z);
    }

    void setValue(float x, float y, float z) {
        __x->setCaption("x:" + std::to_string(x));
        __y->setCaption("y:" + std::to_string(y));
        __z->setCaption("z:" + std::to_string(z));
    }
};

