#pragma once

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <reactphysics3d.h>

namespace OpenGL{
class ICamera {
    public:
        virtual glm::mat4 getViewMatrix() const = 0;

        virtual glm::mat4 getProjectionMatrix(float width, float height) const = 0;

        virtual void setPosition(glm::vec3 position) = 0;

        virtual glm::vec3 getForwardVector() const = 0;

        virtual glm::vec3 getRightVector() const = 0;

        virtual glm::vec3 getUpVector() const = 0;

        virtual glm::vec3 getPosition() const = 0;

        rp3d::Ray castRay(float x1, float y1, float width, float height) {
            float x = (2.0f * x1) / width - 1.0f;
            float y = 1.0f - (2.0f * y1) / height;
            float z = 0.0f;

            glm::vec3 ray_nds =  glm::vec3(x, y, z);
            glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
            glm::vec4 ray_eye =  glm::inverse(getProjectionMatrix(width, height)) * ray_clip;
            ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
            glm::vec3 ray_wor = glm::inverse(getViewMatrix()) * ray_eye;

            ray_wor = glm::normalize(ray_wor);

            auto r = getRightVector();
            auto u = getUpVector();
            auto o = y * u + x * r;

            auto p = getPosition();
            rp3d::Vector3 start(p.x + o.x, p.y + o.y, p.z + o.z);
            rp3d::Vector3 end(p.x + o.x + 1000.0f * ray_wor.x, p.y + o.y + 1000.0f * ray_wor.y, p.z + o.z + 1000.0f * ray_wor.z);
            rp3d::Ray ray(start, end);
            return ray;
        }
    };

class IInteractiveCamera: public ICamera, public Engine::Input::IKeyboardSubscriber, public Engine::Input::IMouseSubscriber {};

}
