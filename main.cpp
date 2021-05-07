#include "ply/saving.h"
#include "programoptionsconfig.hpp"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::chrono;

int main(int argc, char* argv[]) {
    // note the start time
    time_point<system_clock> start = system_clock::now();

    BoostConfig config( argc, argv );
    saveOneFrame(config);

    // note the end time
    time_point<system_clock> end = system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << "s";
}