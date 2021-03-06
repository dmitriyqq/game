#pragma once

#include <Renders/OpenGL/Camera.hpp>
#include <Renders/OpenGL/FpsLikeCamera.hpp>
#include <Engine/IMouseSubscriber.hpp>

#include "ArcBallPositionProvider.hpp"

namespace OpenGL {

    class ArcBallCamera : public OpenGL::FpsLikeCamera, public ArcBallPositionProvider {
        bool __mousePressed = false;
        float __speed = 10.5f;

    public:
        glm::vec3 up = glm::vec3(0, 1, 0);

        ArcBallCamera() {
        }

        void setCenter(glm::vec3 position) {
            __center = position;
        }

        glm::vec3 getCenter() const {
            return __center;
        }

        float getZoom() const { return __orbitRadius; }

        void setZoom(float zoom) { __orbitRadius = zoom; }

        void update(float delta_time, const Engine::Input::IKeyboardState &keyboard) override {

            if (keyboard.isKeyPressed(Engine::Input::Key::DOWN)) {
                auto f = getForwardVector();
                __center.x += -__speed * f.x * delta_time;
                __center.z += -__speed * f.z * delta_time;
            }

            if (keyboard.isKeyPressed(Engine::Input::Key::UP)) {
                auto f = getForwardVector();
                __center.x += __speed * f.x * delta_time;
                __center.z += __speed * f.z * delta_time;
            }

            if (keyboard.isKeyPressed(Engine::Input::Key::LEFT)) {
                auto r = getRightVector();
                __center.x += __speed * r.x * delta_time;
                __center.z += __speed * r.z * delta_time;
            }

            if (keyboard.isKeyPressed(Engine::Input::Key::RIGHT)) {
                auto r = getRightVector();
                __center.x += -__speed * r.x * delta_time;
                __center.z += -__speed * r.z * delta_time;
            }

            if (keyboard.isKeyPressed(Engine::Input::Key::MORE)) {
                __orbitRadius += __speed * delta_time;
            }

            if (keyboard.isKeyPressed(Engine::Input::Key::LESS)) {
                __orbitRadius -= __speed * delta_time;
            }
        }

        glm::mat4 getViewMatrix() const override {
            return glm::lookAt(getPostionVector(), __center, getUpVector());
        }

        void onMouseMove(float x, float y, float dx, float dy) override {
            if (!__mousePressed) {
                return;
            }

            __phi += 0.02 * dx;
            __alpha += 0.02 * dy;
        }

        void onMouseUp(Engine::Input::MouseButton key, float x, float y, int mods) override {
            __mousePressed = false;
        }

        bool onMouseDown(Engine::Input::MouseButton key, float x, float y, int mods) override {
            if (Glfw::KeyMap::isSpecialKeyPressed(mods, Engine::Input::SpecialKey::SHIFT)) {
                __mousePressed = true;
            }

            return false;
        }


        glm::vec3 getForwardVector() const override {
            auto v = getPosition();
            auto d = __center - v;
            return glm::normalize(d);
        }

        glm::vec3 getRightVector() const override {
            auto u = up;
            auto f = getForwardVector();
            auto c = glm::cross(u, f);
            glm::vec3 cameraRight = glm::normalize(c);
            return cameraRight;
        }

        glm::vec3 getUpVector() const override {
            auto f = getForwardVector();
            auto r = getRightVector();
            glm::vec3 cameraUp = glm::cross(f, r);
            return cameraUp;
        }

        glm::vec3 getPosition() const override {
            return getPostionVector();
        }
    };

}