cmake_minimum_required(VERSION 3.16)
project(datasaving)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)


# Save the command line compile commands in the build output
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -march=icelake-client -funroll-loops -Wall -Wextra")

find_package(realsense2 REQUIRED) #added
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)

add_subdirectory(programoptions)

add_executable(datasaving main.cpp
        ply/saving.cpp ply/saving.h
        contextanddevice/devicemanager.cpp contextanddevice/devicemanager.h
        third-party/stb_image_write.h
        programoptions/src/programoptionsconfig.cpp programoptions/include/programoptionsconfig.hpp programoptions/include/configuration.hpp)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
include_directories(./third-party )


target_link_libraries(datasaving PRIVATE
        datasaving::programoptions
        ${Boost_LIBRARIES}
        ${realsense2_LIBRARY}
        )

