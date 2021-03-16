//
// Created by liu on 16/03/2021.
//

#include "devicemanager.h"

void debut()
{
    // Get first rs device
    rs2::context ctx;
    auto list = ctx.query_devices();
    if (list.size() == 0) throw std::runtime_error("No device detected");
    else std::cout << "Device total number :  " << list.size() << std::endl;
    rs2::device dev = list.front();
    std::cout << dev.get_info(RS2_CAMERA_INFO_NAME) << std::endl;
}

