#pragma once

#include <vector>

#include "Vector3f.hpp"
#include "Voxel.hpp"
#include "VoxelSpace.hpp"
#include "IRenderingBackend.hpp"

class Camera
{
    Vector3f _position = {0, 0, 0};
    int _width = 80, _height = 25;

    RenderingBackend *_renderingBackend;

    std::vector<std::vector<Voxel>> _projection;

    void redraw(const ISpace *space)
    {
        projection.assign(_width, std::vector<Voxel>(_height));

        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
            {
                // Coords mapping
                float x = j + _position.x;
                float y = i + _position.y;
                float z = _position.z;

                projection[j][i] = space->get(x, y, z);
            }
        }
    }

  public:
    void move(Vector3f offset)
    {
        _position += offset;
        redraw();
    }

    void display(space)
    {
        redraw(space);
        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
            {
                _renderingBackend.display(projection[j][i]);
            }
        }
    }
};
