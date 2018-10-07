#pragma once

#include "IMouseSubscriber.hpp"

namespace Engine{

    namespace Input{

        class IMouseInput{
        public:
            virtual void addSubscriber(IMouseSubscriber *subscriber) = 0;
        };

    }

}