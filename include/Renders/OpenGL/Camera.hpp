#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ICamera.hpp"

namespace OpenGL {

using glm::vec3;
using glm::mat4;

class Camera : public ICamera {
public:
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    Camera(vec3
    position = vec3(0.0f, 0.0f, 0.0f),
            vec3
    up = vec3(0.0f, 1.0f, 0.0f),
    float yaw = YAW,
    float pitch = PITCH
    );

    virtual ~Camera();

    virtual mat4 getViewMatrix();

    virtual mat4 getProjectionMatrix(float width, float height);

    virtual vec3 getPosition() const { return Position; }

    virtual vec3 getDirection() const { return Front; }

    virtual void setZoom(float yoffset);

    virtual void setView(float xoffset, float yoffset, bool constrainPitch = true);

    virtual void setPosition(Direction direction, float deltaTime);

private:
    static constexpr float YAW = 90.0f;
    static constexpr float PITCH = 0.0f;
    static constexpr float SPEED = 2.5f;
    static constexpr float SENSITIVTY = 0.1f;
    static constexpr float ZOOM = 45.0f;

    float yaw = 0;
    float pitch = 0;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;

    void updateVectors();
};

}