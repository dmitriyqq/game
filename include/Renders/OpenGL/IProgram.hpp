#pragma once

namespace OpenGL {
    class IProgram {
        public:
        virtual void use() const = 0;
    };
}
