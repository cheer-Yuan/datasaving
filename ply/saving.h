//
// Created by liu on 15/03/2021.
//

#ifndef DATASAVING_SAVING_H
#define DATASAVING_SAVING_H

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <fstream>              // File IO
#include <iostream>             // Terminal IO
#include <sstream>              // Stringstreams


// Helper function for writing metadata to disk as a csv file
void metadata_to_csv(const rs2::frame& frm, const std::string& filename);

#endif //DATASAVING_SAVING_H
