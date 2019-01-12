#pragma once

namespace Engine{

    namespace Input{
        enum class MouseButton {LEFT, RIGHT};

        class IMouseSubscriber{
        public:
            virtual void onMouseMove(float x, float y, float dx, float dy) = 0;

            virtual void onMouseUp(MouseButton key, float x, float y, int mods) {};

            virtual void onMouseDown(MouseButton key, float x, float y, int mods) {};
        };
    }

}