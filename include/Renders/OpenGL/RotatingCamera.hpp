#pragma once

#include "ICamera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Engine/IUpdatable.hpp>

namespace OpenGL {

class RotatingCamera : public ICamera, Engine::Input::IUpdatable{
    glm::vec3 __target;
    glm::vec3 __position;
    float __time;
    float __r;
    float zoom = 45.0f;
    float __speed = 0.5f;
    void updatePosition(){
        float cosa = cos(__time);
        float sina = sin(__time);

        __position.x = __target.x + __r * sina;
        __position.y = __target.y + 2.0f;
        __position.z = __target.z + __r * cosa;
    }

    public:
        RotatingCamera(float x = 0, float y = 0, float z = 0, float radius = 1.5f): __target(x, y, z), __r(radius){
            updatePosition();
        }

        glm::mat4 getViewMatrix() const override {
            return glm::lookAt(__position, __target, glm::vec3(0, 1, 0));
        }

        glm::mat4 getProjectionMatrix(float width, float height) const override {
            return glm::perspective(zoom, width / height, 0.1f, 150.0f);
        }

        void update(float delta_time, Engine::Input::IKeyboardState &keyboard) override {
            __time+=__speed * delta_time;
            updatePosition();
        }

        void setPosition(glm::vec3 position) {
            __position = position;
        }
    };

}