#pragma once

namespace Engine{

    namespace Input{
        class IMouseSubscriber{
        public:
            virtual void update(double x, double y, double dx, double dy) = 0;
        };
    }

}