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

    void setPosition(glm::vec3 position) override  {
        Position = position;
    };

    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f),
           vec3 up = vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW,
           float pitch = PITCH
          ): movementSpeed(SPEED),
             mouseSensitivity(SENSITIVITY),
             zoom(ZOOM)
    {
        Front = vec3(0.0f, 0.0f, -1.0f);
        Position = position;
        WorldUp = up;
        Up = up;
        this->yaw = yaw;
        this->pitch = pitch;
        updateVectors();
    }


    virtual ~Camera() = default;

    mat4 getViewMatrix() const override {
        return glm::lookAt(Position, Position + Front, Up);
    }

    mat4 getProjectionMatrix(float width, float height) const override {
        return glm::perspective(zoom, width / height, 0.1f, 1000.0f);
    }

    virtual vec3 getPosition() const override { return Position; }

    virtual vec3 getDirection() const { return Front; }

    virtual void setZoom(float yoffset) {
        if (zoom >= 1.0f && zoom <= 45.0f)
            zoom -= yoffset;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 45.0f)
            zoom = 45.0f;
    }

    virtual void setView(float xoffset, float yoffset, bool constrainPitch = true){
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw -= xoffset;
        pitch -= yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Eular angles
        updateVectors();
    }

    virtual void setPosition(Direction direction, float deltaTime) {
        float velocity = movementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    glm::vec3 getForwardVector() const override { return Front; }

    glm::vec3 getRightVector() const override { return Right; }

    glm::vec3 getUpVector() const override { return Up; }

    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;


private:
    static constexpr float YAW = 90.0f;
    static constexpr float PITCH = 0.0f;
    static constexpr float SPEED = 2.5f;
    static constexpr float SENSITIVITY = 0.1f;
    static constexpr float ZOOM = 45.0f;

    float yaw = 0;
    float pitch = 0;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void updateVectors() {
        using glm::radians;
        vec3 front;
        front.x = cos(radians(yaw)) * cos(radians(pitch));
        front.y = sin(radians(pitch));
        front.z = sin(radians(yaw)) * cos(radians(pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front,
                                        WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

}
