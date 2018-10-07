#include "Renders/OpenGL/Camera.hpp"
#include <iostream>

namespace OpenGL {

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch)
        : movementSpeed(SPEED),
          mouseSensitivity(SENSITIVTY),
          zoom(ZOOM) {
    Front = vec3(0.0f, 0.0f, -1.0f);
    Position = position;
    WorldUp = up;
    Up = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateVectors();
}

Camera::~Camera() {

}

mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

mat4 Camera::getProjectionMatrix(float width, float height) {
    return glm::perspective(zoom, width / height, 0.1f, 100.0f);
}

void Camera::setView(float xoffset, float yoffset, bool constrainPitch) {
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

void Camera::updateVectors() {
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

void Camera::setZoom(float yoffset) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::setPosition(Direction direction, float deltaTime) {
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

}