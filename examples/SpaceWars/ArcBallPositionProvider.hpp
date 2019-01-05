#pragma once

#include <Renders/OpenGL/IPositionProvider.hpp>
#include <cmath>
#include <glm/glm.hpp>

class ArcBallPositionProvider : public OpenGL::IPositionProvider {
protected:
    float __orbitRadius;
    float __alpha;
    float __phi;
    glm::vec3 __center;

    public:
        ArcBallPositionProvider(glm::vec3 center = glm::vec3(0),
                                float radius = 1.0f,
                                float phi = 0.0,
                                float alpha = 2.5f):
            __orbitRadius(radius), __center(center), __phi(phi), __alpha(alpha) {
        }

    glm::mat4 getPositionMatrix() const override {
        auto model = glm::mat4(1);
        model = glm::translate(model, getPostionVector());
        return model;
    }

    glm::vec3 getPostionVector() const override {
        float x = __center.x + __orbitRadius * std::sin(__phi);
        float y = __center.y + __orbitRadius * std::sin(__alpha);
        float z = __center.z + __orbitRadius * std::cos(__phi);
        return glm::vec3(x, y, z);
    }

    void setPosition(float phi) {
        __phi = phi;
    }

    glm::vec3 getTarget() const {
        return __center;
    }
};