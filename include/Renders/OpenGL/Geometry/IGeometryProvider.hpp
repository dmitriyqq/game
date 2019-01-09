#pragma once

#include <Renders/OpenGL/Vertex.hpp>

#include <vector>

namespace OpenGL {
  template <class V>
  class IGeometryProvider {
  public:
    virtual std::vector<V> getData() const = 0;
  };

}
