#include <iostream>
#include "ply/saving.h"

int main() {

    rs2::pointcloud pc;
    rs2::points points;
    rs2::pipeline pipe;

    // Start streaming with default recommended configuration
    pipe.start();

    auto frames = pipe.wait_for_frames();
    auto depth = frames.get_depth_frame();
    auto color = frames.get_color_frame();


    // Wait for the next set of frames from the camera. Now that autoexposure, etc.
    // has settled, we will write these to disk
    for (auto&& frame : pipe.wait_for_frames())
    {
        // We can only save video frames as pngs, so we skip the rest
        if (auto vf = frame.as<rs2::video_frame>())
        {
            auto stream = frame.get_profile().stream_type();

            // Write images to disk
            pc.map_to(color);
            points = pc.calculate(depth);
            points.export_to_ply("first.ply", color);


            // Record per-frame metadata for UVC streams
            std::stringstream csv_file;
            csv_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name()
                     << "-metadata.csv";
            metadata_to_csv(vf, csv_file.str());
        }
    }
}
