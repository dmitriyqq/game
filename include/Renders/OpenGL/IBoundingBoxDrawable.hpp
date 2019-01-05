#pragma once

#include <Renders/IDrawable.hpp>
#include <Renders/OpenGL/IBoundingBox.hpp>

namespace OpenGL{
    class IBoundingBoxDrawable: public IDrawable, public IBoundingBox {};
}