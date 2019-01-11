#pragma once

#include <nanogui/nanogui.h>
#include <glm/glm.hpp>
#include <string>

class VectorWidget : public nanogui::Widget {
    nanogui::Label *__x, *__y, *__z;

    nanogui::BoxLayout *__layout = nullptr;
public:
    VectorWidget(nanogui::Widget *parent): nanogui::Widget(parent) {
        __layout = new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum);
        setLayout(__layout);
        __layout->setMargin(0);
        __layout->setSpacing(0);
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

//        setWidth(100.0f);
//        setHeight(50.0f);
    }
};

