#pragma once

#include <Renders/OpenGL/RectangleVAO.hpp>
#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/PositionShaderProgram.hpp>
#include <Renders/OpenGL/Camera2D.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace OpenGL{

class Rectangle: public Mesh {
    float __x, __y, __width, __height;
public:
    Rectangle(float x, float y, float w, float h,
    PositionShaderProgram *program, RectangleVAO *rectangle):
        Mesh(program, rectangle)
    {
        initialize(x, y, w, h);
    }

    void initialize(float x, float y, float w, float h){
         __x = x;
        __y = y;
        __width = w;
        __height = h;

        setPosition(x + __width / 2.0f - w / 2.0f,
                    y + __height / 2.0f - h / 2.0f, 0.0f);

        setScale(w, h, 0.0f);
    }


};

class Graphics2D {
    PositionShaderProgram *__program = nullptr;
    RectangleVAO *__rectangle = nullptr;
    Camera2D *__camera = nullptr;
    int __width, __height;

    public:
    Graphics2D(int width, int height): __width(width), __height(height) {
        __rectangle = new OpenGL::RectangleVAO();
        __program = new OpenGL::PositionShaderProgram();
        __program->loadShaders("./sharedAssets/shaders/2dshader.vert", "./sharedAssets/shaders/2dshader.frag");
        __camera = new Camera2D();
        __program->setCamera(__camera, width, height);
    }

    static Graphics2D* get(){
        static Graphics2D graphics(600, 600); 
        return &graphics;
    }

    void setScreenSize(int width, int height) {
        __program->setCamera(__camera, width, height);
        __width = width;
        __height = height;
    }

    Rectangle* getRectangleWH(float x, float y, float w, float h) {
        auto mesh = new Rectangle(x, y, w, h, __program, __rectangle);
        return mesh;
    }

    Rectangle* getRectangleXY(float x1, float y1, float x2, float y2) {
        return getRectangleWH(x1, y1, x2 - x1, y2 - y1);
    }
};

}