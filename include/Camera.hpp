#pragma once

#include <vector>

#include "Vector3i.hpp"
#include "Vector3f.hpp"
#include "Voxel.hpp"
#include "VoxelSpace.hpp"
#include "IRenderingBackend.hpp"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class Camera
{
    Vector3f _position = {0, 0, 0};
    int _width = 80, _height = 25;

    IRenderingBackend *_renderingBackend;

    std::vector<std::vector<Voxel>> _projection;

    void redraw(const ISpace *space)
    {
        _projection.assign(_width, std::vector<Voxel>(_height));

        auto my_logger = spdlog::basic_logger_mt("basic_logger", "basic-log.txt");
        my_logger->error("Welcome to spdlog!");
        my_logger->flush();

        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
            {
                // Coords mapping
                int x = j + _position.x;
                int y = i + _position.y;
                int z = _position.z;

                Vector3i voxel_pos = {x, y, z};
                _projection[j][i] = space->get(voxel_pos);
            }
        }
    }

  public:
    Camera(){
        _renderingBackend = new NCursesRenderingBackend();
    }

    void move(Vector3f offset)
    {
        _position += offset;
    }

    void display(const ISpace *space)
    {
        redraw(space);
        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
            {
                _renderingBackend->display(_projection[j][i]);
            }
        }
    }
};
