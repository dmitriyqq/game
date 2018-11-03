#pragma once

#include "IKeyboardSubscriber.hpp"

namespace Engine {

    namespace Input {

        class IKeyboardDirectInput {
        public:
            virtual void addSubscriber(IKeyboardSubscriber *subscriber) = 0;
        };

    }

}