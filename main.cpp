#include "ply/saving.h"
#include "programoptionsconfig.hpp"
#include "fstream"

int main(int argc, char* argv[]) {
    // need to add a start timestamp
    std::string currenttime = GetLocalTimeWithMs();
    std::ofstream out("log.txt");
    out << currenttime << std::endl;
    out.close();

    BoostConfig config( argc, argv );
    SaveOneFrame(config);
}