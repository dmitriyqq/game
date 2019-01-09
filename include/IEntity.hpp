#pragma once

namespace Engine {

    class IEntity : public IDrawable, public Input::IUpdatable {

    public:
        virtual void update(float delta_time) = 0;

        virtual void draw() const = 0;
    };

}