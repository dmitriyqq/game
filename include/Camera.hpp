#pragma once

#include <vector>
#include <ncurses.h>

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
    int _width = 50, _height = 50;

    IRenderingBackend *_renderingBackend;

    std::vector<std::vector<Voxel>> _projection;

    void redraw(const ISpace *space)
    {
        _projection.assign(_width, std::vector<Voxel>(_height));

        auto logger = spdlog::get("main_logger");

        logger->info("start projecting");
        constexpr int depth = 100;
        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++)
            {
                for (int k = 0; k < depth; k++) {
                    // Coords mapping
                    int x = j + _position.x;
                    int y = i + _position.y;
                    int z = k + _position.z;


                    Vector3i voxel_pos = {x, y, z};
                    auto voxel = space->get(voxel_pos);

                    if ((voxel.type != Voxel::Type::AIR))
                        _projection[j][i] = Voxel(voxel);
                }
            }
        }

        logger->info("end projecting");
        logger->debug("debug projecting");
        for (int i = 0; i < _height; i++)
        {
            for (int j = 0; j < _width; j++) {
                auto voxel = _projection[i][j];
                logger->debug("voxel screen({}, {}) model:({}, {}, {}) - type: {}", i, j, voxel.position.x, voxel.position.y, voxel.position.z, (int) voxel.type);
            }
        }
        logger->debug("end debug projecting");
    }

  public:
    Camera(){
        _renderingBackend = new NCursesRenderingBackend();
        _width = _renderingBackend->width();
        _height = _renderingBackend->height();

        auto logger = spdlog::get("main_logger");
        logger->info("GET WIDTH = {}", _width);
        logger->info("GET HEIGHT = {}", _height);
        logger->flush();
    }

    int width(){
        return _renderingBackend->width();
    }

    int height(){
        return _renderingBackend->height();
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
                _renderingBackend->display(_projection[j][i], i, j);
            }
        }
        refresh();
    }

    const IRenderingBackend* getBackend(){
        return _renderingBackend;
    }

};
