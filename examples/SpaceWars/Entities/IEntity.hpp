#pragma once

#include <Renders/OpenGL/Mesh.hpp>
#include <Renders/OpenGL/IBoundingBoxDrawable.hpp>
#include <Renders/OpenGL/BoundingBox.hpp>
#include <Renders/OpenGL/Graphics2D.hpp>
#include <Engine/ISelectable.hpp>
#include <Renders/OpenGL/Utils.hpp>

#include <vector>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <reactphysics3d.h>

class IEntity : public IDrawable {

public:
    virtual void update(float __delta_time) = 0;
};