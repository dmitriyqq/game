#pragma once

#include "Input.hpp"

namespace Engine{
    namespace Input {
        class IKeyboardState {
        public:
            virtual bool isKeyPressed(Key key) = 0;
        };
    }
}