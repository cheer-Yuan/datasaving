//
// Created by liu on 15/03/2021.
//

#include "saving.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <sys/time.h>

// get the current time in ms
static std::string GetLocalTimeWithMs(void)
{
    std::string defaultTime = "19700101000000000";
    try
    {
        struct timeval curTime;
        gettimeofday(&curTime, NULL);
        int milli = curTime.tv_usec / 1000;

        char buffer[80] = {0};
        struct tm nowTime;
        localtime_r(&curTime.tv_sec, &nowTime);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d-%H:%M:%S:", &nowTime);

        char currentTime[84] = {0};
        snprintf(currentTime, sizeof(currentTime), "%s%03d-", buffer, milli);

        return currentTime;
    }
    catch(const std::exception& e)
    {
        return defaultTime;
    }
    catch (...)
    {
        return defaultTime;
    }
}

void metadataToCsv(const rs2::frame& frm, const std::string& filename){
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

/* saveKernel Saves one group od data to the disk
 */
void saveKernel(const rs2::colorizer& color_map, const rs2::pipeline& pipe, int ifPly, int ifDepth, int ifColor, int ifInfr, int ifColor){
//    time_t t = time(0);
//    char tmp[32];
//    strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H:%M:%S-",localtime(&t));
    std::string currenttime = GetLocalTimeWithMs();

    // Wait until a new set of frames become available
    rs2::frameset frames = pipe.wait_for_frames();

    // write the point cloud to disk
    if (ifPly) {
        // Get the first depth and color frame
        auto depth = frames.get_depth_frame();
        auto color = frames.get_color_frame();

        rs2::pointcloud pc;
        // Map the point cloud to the given color frame
        pc.map_to(color);
        // Generate the pointcloud and texture mappings of depth map.
        rs2::points points = pc.calculate(depth);

        // Export the point cloud to a PLY file with or without colors
        std::stringstream ply_file;
        ply_file << "../output/" << currenttime << "Points.ply";
        if (ifColor == 1) {
            points.export_to_ply(ply_file.str(), color);

        }
        points.export_to_ply_notexture(ply_file.str());
        std::cout << "Saved " << ply_file.str() << std::endl;
    }

    // write images to disk
    for (auto&& frame : frames)
    {
        // we can only save video frames as pngs, so we skip the rest
        if (auto vf = frame.as<rs2::video_frame>())
        {
            // use the colorizer to get an rgb image for the depth stream
            if (vf.is<rs2::depth_frame>()) vf = color_map.process(frame);

            // write the corresponding the images to disk, according to the given parameters
            std::stringstream png_file;

            if (vf.get_profile().stream_name() == "Depth") {
                if (ifDepth) {
                    png_file << "../output/" << currenttime << vf.get_profile().stream_name() << ".png";
                    stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(), vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
                    std::cout << "Saved " << png_file.str() << std::endl;

                    // record the metadata
                    std::stringstream csv_file;
                    csv_file << "../output/" << currenttime << vf.get_profile().stream_name()
                             << "-metadata.csv";
                    metadataToCsv(vf, csv_file.str());
                }
            }

            if (vf.get_profile().stream_name() == "Infrared") {
                if (ifInfr) {
                    png_file << "../output/" << currenttime << vf.get_profile().stream_name() << ".png";
                    stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(), vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
                    std::cout << "Saved " << png_file.str() << std::endl;

                    // record the metadata
                    std::stringstream csv_file;
                    csv_file << "../output/" << currenttime << vf.get_profile().stream_name()
                             << "-metadata.csv";
                    metadataToCsv(vf, csv_file.str());
                }
            }

            if (vf.get_profile().stream_name() == "Color") {
                if (ifColor) {
                    png_file << "../output/" << currenttime << vf.get_profile().stream_name() << ".png";
                    stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(), vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
                    std::cout << "Saved " << png_file.str() << std::endl;

                    // record the metadata
                    std::stringstream csv_file;
                    csv_file << "../output/" << currenttime << vf.get_profile().stream_name()
                             << "-metadata.csv";
                    metadataToCsv(vf, csv_file.str());
                }
            }
        }
    }
}

void saveOneFrame(const BoostConfig& config){
    // count the seconds
    struct timeval t1, t2;
    double timeuse;
    gettimeofday(&t1,NULL);

    // Start streaming with default recommended configuration
    rs2::pipeline pipe;
    pipe.start();

    // save the parameters to a txt.file
    std::ofstream parameterFile;
    parameterFile.open("parameters.txt", std::ios::out | std::ios::trunc);
    if (parameterFile.is_open()) {
        parameterFile << config.give_photos() << "\n" << config.give_interval() << "\n";
    }
    parameterFile.close();

    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // if the parameter = -1, enter the infinite loop mode
    if (config.give_photos() == -1)
        saveInfiniteFrames(color_map, pipe, config.give_interval(), config.if_ply(), config.if_depth(), config.if_rgb(),
                           config.if_infrarouge(), t1);

    // Iterate on the total number of images to be saved
    for (int i = 0; i < config.give_photos(); ++i) {
        // note down the start of one iteration
        if (i != 0) {
            gettimeofday(&t1,NULL);
        }

        saveKernel(color_map, pipe, config.if_ply(), config.if_depth(), config.if_rgb(), config.if_infrarouge());

        // save the counter in a file
        parameterFile.open("parameters.txt", std::ios::out | std::ios::app);
        if (parameterFile.is_open()) {
            parameterFile << i << "\n";
        }
        parameterFile.close();

        // sleep if the value of the time interval is longer than the time spent for recording
        gettimeofday(&t2,NULL);
        timeuse = (config.give_interval() * 1000) - (t2.tv_sec - t1.tv_sec) * 1000 - (double)(t2.tv_usec - t1.tv_usec)/1000.0;
        if (timeuse > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(timeuse)));
        }
    }
}

void saveInfiniteFrames(rs2::colorizer color_map, rs2::pipeline pipe, int interv, int ifPly, int ifDepth, int ifColor, int ifInfr, struct timeval t1){
    // count the number of data saved
    int counter = 0;

    // Save a group of data within an infinite loop
    while (true) {
        struct timeval t2;
        double timeuse;

        // note down the start of one iteration
        if (counter != 0) {
            gettimeofday(&t1,NULL);
        }

        // save the counter in a file
        std::ofstream parameterFile;
        parameterFile.open("parameters.txt", std::ios::out | std::ios::app);
        if (parameterFile.is_open()) {
            parameterFile << counter << "\n";
        }
        parameterFile.close();

        saveKernel(color_map, pipe, ifPly, ifDepth, ifColor, ifInfr);

        counter += 1;

        //std::cout << counter << " groups of data saved" << std::endl;

        // sleep if the value of the time interval is longer than the time spent for recording
        gettimeofday(&t2,NULL);
        timeuse = (interv * 1000) - (t2.tv_sec - t1.tv_sec) * 1000 - (double)(t2.tv_usec - t1.tv_usec)/1000.0;
        if (timeuse > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(timeuse)));
        }
    }
}


