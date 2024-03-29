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
#include <thread>
#include "configuration.hpp"
#include <programoptionsconfig.hpp>

// Helper function for writing metadata to disk as a csv file
void metadataToCsv(const rs2::frame& frm, const std::string& filename);

void SaveKernel(const rs2::colorizer& color_map, const rs2::pipeline& pipe, int ifPly, int ifDepth, int ifImages, int ifInfr, int ifColor);

// Save a single frame
void SaveOneFrame(const BoostConfig& config);

void SaveInfiniteFrames(rs2::colorizer color_map, rs2::pipeline pipe, int interv, int ifPly, int ifDepth, int ifImages, int ifInfr, int ifColor, struct timeval t1);

std::string GetLocalTimeWithMs();

#endif //DATASAVING_SAVING_H
