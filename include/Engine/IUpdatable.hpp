#pragma once

#include "IKeyboardState.hpp"

namespace Engine {

    namespace Input {

        class IUpdatable {
        public:
            virtual void update(float delta_time) = 0;
        };

        class IUpdatableKeytable {
        public:
            virtual void update(float delta_time, IKeyboardState &state) = 0;
        };

    }

}