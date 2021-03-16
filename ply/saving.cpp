//
// Created by liu on 15/03/2021.
//

#include "saving.h"

void metadata_to_csv(const rs2::frame& frm, const std::string& filename)
{
    std::ofstream csv;

    csv.open(filename);

    //    std::cout << "Writing metadata to " << filename << endl;
    csv << "Stream," << rs2_stream_to_string(frm.get_profile().stream_type()) << "\nMetadata Attribute,Value\n";

    // Record all the available metadata attributes
    for (size_t i = 0; i < RS2_FRAME_METADATA_COUNT; i++)
    {
        if (frm.supports_frame_metadata((rs2_frame_metadata_value)i))
        {
            csv << rs2_frame_metadata_to_string((rs2_frame_metadata_value)i) << ","
                << frm.get_frame_metadata((rs2_frame_metadata_value)i) << "\n";
        }
    }

    csv.close();
}

void save_one_frame(const char* filename)
{
    // Start streaming with default recommended configuration
    rs2::pipeline pipe;
    pipe.start();

    // Wait until a new set of frames become available
    rs2::frameset frames = pipe.wait_for_frames();

    // Get the first depth and color frame
    auto depth = frames.get_depth_frame();
    auto color = frames.get_color_frame();

    rs2::pointcloud pc;
    // Map the point cloud to the given color frame
    pc.map_to(color);
    // Generate the pointcloud and texture mappings of depth map.
    rs2::points points = pc.calculate(depth);

    // Export the point cloud to a PLY file
    points.export_to_ply(filename, color);

    // Record per-frame metadata for UVC streams
    std::stringstream csv_file;
    csv_file << "rs-save-to-disk-output-" << frames.get_profile().stream_name()
             << "-metadata.csv";
    metadata_to_csv(frames, csv_file.str());

//    // Wait for the next set of frames from the camera. Now that autoexposure, etc.
//    // has settled, we will write these to disk
//    for (auto&& frame : pipe.wait_for_frames())
//    {
//        // We can only save video frames as pngs, so we skip the rest
//        if (auto vf = frame.as<rs2::video_frame>())
//        {
//            auto stream = frame.get_profile().stream_type();
//
//
//
//
//        }
//    }
}


void save_one_video_clip(const char* filename)
{
    // Declare frameset and frames which will hold the data from the camera
    rs2::frameset frames;
    rs2::frame depth;

    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // Create a shared pointer to a pipeline
    auto pipe = std::make_shared<rs2::pipeline>();

    // Start streaming with default configuration
    pipe->start();

    // Initialize a shared pointer to a device with the current device on the pipeline
    rs2::device device = pipe->get_active_profile().get_device();

    // If the device is sreaming live and not from a file
    if (!device.as<rs2::playback>())
    {
        frames = pipe->wait_for_frames(); // wait for next set of frames from the camera
        depth = color_map.process(frames.get_depth_frame()); // Find and colorize the depth data
    }

    if (!device.as<rs2::playback>()) // Disable recording while device is playing
    {
        // Record
        pipe->stop(); // Stop the pipeline with the default configuration
        pipe = std::make_shared<rs2::pipeline>();
        rs2::config cfg; // Declare a new configuration
        cfg.enable_record_to_file(filename);
        pipe->start(cfg); //File will be opened at this point
        device = pipe->get_active_profile().get_device();

        sleep(12);

        // Stop
        pipe->stop(); // Stop the pipeline that holds the file and the recorder
        pipe = std::make_shared<rs2::pipeline>(); //Reset the shared pointer with a new pipeline
        pipe->start(); // Resume streaming with default configuration
        device = pipe->get_active_profile().get_device();
    }
}

void play_the_clip(const char* filename)
{
    // Declare frameset and frames which will hold the data from the camera
    rs2::frameset frames;
    rs2::frame depth;

    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // Create a shared pointer to a pipeline
    auto pipe = std::make_shared<rs2::pipeline>();

    // Start streaming with default configuration
    pipe->start();

    // Initialize a shared pointer to a device with the current device on the pipeline
    rs2::device device = pipe->get_active_profile().get_device();

    if (!device.as<rs2::playback>())
    {
        pipe->stop(); // Stop streaming with default configuration
        pipe = std::make_shared<rs2::pipeline>();
        rs2::config cfg;
        cfg.enable_device_from_file(filename);
        pipe->start(cfg); //File will be opened in read mode at this point
        device = pipe->get_active_profile().get_device();
    }
    else
    {
        device.as<rs2::playback>().resume();
    }
}