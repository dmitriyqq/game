#pragma once

#include <nanogui/widget.h>
#include "../UnitsFactory.hpp"
#include "../MapSelector.hpp"
#include <Engine/IUpdatable.hpp>

class EntityFactoryWindow:
        public nanogui::Window,
        public Engine::Input::IUpdatable,
        public IDrawable,
        public Engine::Input::IMouseSubscriber {
    nanogui::ImagePanel *__panel;
    Player *__player = nullptr;
    MapSelector *__selector = nullptr;
    UnitsFactory *__factory = nullptr;

    Unit *__unit = nullptr;
public:
    EntityFactoryWindow(nanogui::Screen *parent, MapSelector *selector, Player *player, UnitsFactory *factory, float width):
            nanogui::Window(parent, "Create Units"),
            __player(player),
            __selector(selector),
            __factory(factory) {
        setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Maximum));
        __panel = new nanogui::ImagePanel(this);
        auto units = factory->getAvailableUnits();

        std::vector<std::pair<int, std::string>> vec = nanogui::loadImageDirectory(parent->nvgContext(), "./sharedAssets/icons/units/");

        __panel->setImages(vec);
        __panel->setWidth(width);
        __panel->setCallback([this, units](int i) {
            delete __unit;
            __unit = __factory->constructUnit(units[i], __player);
        });
    }

    void draw() const override {
        if (__unit != nullptr) {
            __unit->draw();
        }
    }

    void update(float delta_time) override {
        if (__unit != nullptr) {
            __unit->update(delta_time);
            __unit->setRotation();
            __unit->setPosition(__selector->getSelectedPoint());
        }
    }

    void onMouseMove(float x, float y, float dx, float dy) override {

    }

    virtual bool onMouseDown(Engine::Input::MouseButton key, float x, float y, int mods) {
        if (__unit) {
            __player->addEntity(__unit);
        }
        __unit = nullptr;
        return true;
    };


};

