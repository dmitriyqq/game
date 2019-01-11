#pragma once

#include <Engine/Input.hpp>
#include <GLFW/glfw3.h>

namespace Glfw {

    class KeyMap {
        using KeyType = Engine::Input::Key;
    public:
        Engine::Input::Key map(int glfw_key) const {
            switch (glfw_key) {
                case GLFW_KEY_W:
                    return KeyType::UP;
                case GLFW_KEY_S:
                    return KeyType::DOWN;
                case GLFW_KEY_A:
                    return KeyType::LEFT;
                case GLFW_KEY_D:
                    return KeyType::RIGHT;
                case GLFW_KEY_SPACE:
                    return KeyType::ACTION;
                case GLFW_KEY_ENTER:
                    return KeyType::ACCEPT;
                case GLFW_KEY_ESCAPE:
                    return KeyType::EXIT;
                case GLFW_KEY_Q:
                    return KeyType::MORE;
                case GLFW_KEY_E:
                    return KeyType::LESS;
                default:
                    return KeyType::ACTION;
            }
        }

        int map(Engine::Input::Key key) const {

            switch (key) {
                case KeyType::UP:
                    return GLFW_KEY_W;
                case KeyType::DOWN:
                    return GLFW_KEY_S;
                case KeyType::LEFT:
                    return GLFW_KEY_A;
                case KeyType::RIGHT:
                    return GLFW_KEY_D;
                case KeyType::ACTION:
                    return GLFW_KEY_SPACE;
                case KeyType::ACCEPT:
                    return GLFW_KEY_ENTER;
                case KeyType::EXIT:
                    return GLFW_KEY_ESCAPE;
                default:
                    return GLFW_KEY_ESCAPE;
            }
        }
    };

}