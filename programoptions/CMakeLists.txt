cmake_minimum_required(VERSION 3.16)

add_library(programoptions
        src/programoptionsconfig.cpp
        )

target_include_directories(programoptions PUBLIC include/)
add_library(datasaving::programoptions ALIAS programoptions)
