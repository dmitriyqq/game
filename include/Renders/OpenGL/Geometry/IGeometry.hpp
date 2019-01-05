#pragma once

#include <glad/glad.h>

/**
 * \class Geometry
 *
 * \brief manages vertex data of an object
 *
 * This class creates geometry data and passes it to OpenGL
 *
*/

namespace OpenGL {

 class IGeometry {
 public:
     // Draw geometry on current OpenGL context;
     // Basically performs OpenGL call with appropriate GL primitive
     // with stored parameters
     virtual void draw() const = 0;


     // use explicitly defined parameters
     virtual void draw(GLenum mode, int first, int count) const = 0;
 };

}

