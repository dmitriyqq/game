#pragma once

#include "Input.hpp"

namespace Engine {

    namespace Input {

        class IKeyboardSubscriber {
        public:
            virtual void processKey(Key key) = 0;
        };

    }
}