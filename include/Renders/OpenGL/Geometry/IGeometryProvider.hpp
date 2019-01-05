#pragma once

#include <Renders/OpenGL/Vertex.hpp>

#include <vector>

namespace OpenGL {

  class IGeometryProvider {
  public:
    virtual std::vector<Vertex> getData() const = 0;
  };

}
