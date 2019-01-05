#pragma once

namespace Engine{

    namespace Input{
        enum class MouseButton {LEFT, RIGHT};

        class IMouseSubscriber{
        public:
            virtual void update(double x, double y, double dx, double dy) = 0;

            virtual void onMouseUp(MouseButton key) {};

            virtual void onMouseDown(MouseButton key) {};
        };
    }

}