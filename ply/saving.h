//
// Created by liu on 15/03/2021.
//

#ifndef DATASAVING_SAVING_H
#define DATASAVING_SAVING_H



#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <fstream>              // File IO
#include <iostream>             // Terminal IO
#include <sstream>              // Stringstreams
#include <unistd.h>

// Helper function for writing metadata to disk as a csv file
void metadata_to_csv(const rs2::frame& frm, const std::string& filename);

// Save a single frame
void save_one_frame(const char* filename);

// Seve a videoclip for 3 seconds
void save_one_video_clip(const char* filename);

void play_the_clip(const char* filename);


#endif //DATASAVING_SAVING_H
