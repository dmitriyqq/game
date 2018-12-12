#pragma once

#include "../Engine/IKeyboardState.hpp"
#include "../Engine/IKeyboardDirectInput.hpp"
#include "../Engine/IMouseInput.hpp"
//#include "./OpenGL/ShaderProgram.hpp"

class IWindow{

protected:
    int __width, __height;
public:
    IWindow(int width=600, int height=600): __width(width), __height(height) {}

    virtual Engine::Input::IKeyboardState* getKeyBoardState() = 0;
    virtual Engine::Input::IKeyboardDirectInput *getKeyboardDirectInput() = 0;
    virtual Engine::Input::IMouseInput *getMouseInput() = 0;

    virtual void startDisplay() = 0;
    virtual void endDisplay() = 0;
//    virtual void useShaders(OpenGL::ShaderProgram *program) = 0;

    int getWidth() const {
        return __width;
    }

    int getHeight() const {
        return __height;
    }

};