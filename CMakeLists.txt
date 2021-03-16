cmake_minimum_required(VERSION 3.17)
project(datasaving)

set(CMAKE_CXX_STANDARD 14)

# Save the command line compile commands in the build output
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(realsense2 REQUIRED) #added

add_executable(datasaving main.cpp ply/saving.cpp ply/saving.h contextanddevice/devicemanager.cpp contextanddevice/devicemanager.h)

target_link_libraries(datasaving ${realsense2_LIBRARY}) #added

