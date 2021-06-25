#pragma once

// library headers
#include "configuration.hpp"
#include <boost/program_options.hpp>

/** An implementation of Configuration that reads the parameters using the
 * library Boost.Program_options
 */
class BoostConfig:
        public Configuration
{
    std::string dir;

    // the number of photos to take
    int nb;

    // the time interval between 2 images in seconds
    int interval;

    // whether the normal rgb image will be saved
    int rgb;

    // whether the depth image will be saved
    int depth;

    // whether the infrarouge image will be saved
    int infra;

    // whether the pointcloud will be generated in the .ply format
    int ply;

    // whether save the point with colors
    int color;

    // whether use the default higher resolution or the lowered aresolution
    int lowres;

public:
    /** Construct a new B
     * @param argc the number of command-line arguments
     * @param argv the values of command-line arguments
     */
    BoostConfig(const int argc, const char* const argv[]);

    std::string give_direction() const override { return dir; }

    // see overridden function
    int give_photos() const override { return nb; }

    // see overridden function
    int give_interval() const override { return interval; }

    // see overridden function
    int if_rgb() const override { return rgb; }

    // see overridden function
    int if_depth() const override { return depth; }

    // see overridden function
    int if_infrarouge() const override { return infra; }

    // see overridden function
    int  if_ply() const override { return ply; }

    // see the choice of within or without colors
    int  if_color() const override { return color; }

    // see the choice of default resolution or lower resolution
    int  if_lowres() const override { return lowres; }

};
