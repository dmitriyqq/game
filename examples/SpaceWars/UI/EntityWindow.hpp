#pragma once

#include <nanogui/nanogui.h>
#include "../Players/Player.hpp"

class EntityWindow: public nanogui::Window {
    nanogui::Label *__entityName = nullptr;
    nanogui::Label *__entityPlayer = nullptr;
    nanogui::Label *__health = nullptr;
    nanogui::Label *__armor = nullptr;
    nanogui::ImageView *__view = nullptr;

    const std::string &__name;
    const std::string &__playerName;
    const float &__healthValue;
    const float &__armorValue;

public:
    EntityWindow(nanogui::Widget *parent,
                 const std::string & name,
                 const std::string &playerName,
                 const float &health,
                 const float &armor,
                 unsigned int imageId):
        nanogui::Window(parent, "Name"),
        __name(name),
        __playerName(playerName),
        __healthValue(health),
        __armorValue(armor)
    {
        setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Minimum));
        __entityPlayer = new nanogui::Label(this, __playerName);
        __health = new nanogui::Label(this, std::to_string(__healthValue));
        __armor = new nanogui::Label(this, std::to_string(__armorValue));
        __view = new nanogui::ImageView(this, imageId);
        __view->setWidth(64);
        __view->setHeight(64);
    }


    ~EntityWindow() {}

};
