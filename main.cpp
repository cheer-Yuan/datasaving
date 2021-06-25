#include "ply/saving.h"
#include "programoptionsconfig.hpp"

int main(int argc, char* argv[]) {
    BoostConfig config( argc, argv );
    saveOneFrame(config);
}