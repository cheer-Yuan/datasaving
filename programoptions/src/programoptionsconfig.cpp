#include <fstream>
#include "iostream"
#include <time.h>
#include "programoptionsconfig.hpp"
#include <boost/program_options.hpp>

using namespace boost;
using namespace std;
namespace po = boost::program_options;

BoostConfig::BoostConfig( const int argc, const char* const argv[] )
{
    po::options_description config("Program options");
    config.add_options()
            ("nb,n", po::value<int>(&nb)->default_value(-1), "number of photos to take")
            ("pause,i", po::value<int>(&interval)->default_value(0), "number of photos to take")
            ("rgb,r", po::value<int>(&rgb)->default_value(0), "whether the normal rgb image will be saved")
            ("depth,d", po::value<int>(&depth)->default_value(0), "whether the depth image will be saved")
            ("infrarouge,f", po::value<int>(&infra)->default_value(0), "whether the infrarouge image will be saved")
            ("ply,p", po::value<int>(&ply)->default_value(1), "whether pointcloud will be generated in the .ply format")
            ("color,c", po::value<int>(&color)->default_value(0), "save the point cloud within or without colors (the latter will be faster)")
            ("lowresolution,l", po::value<int>(&lowres)->default_value(2), "save the point cloud within or without colors (the latter will be faster)");

    po::variables_map vm;


    try{
        po::store(parse_command_line(argc, argv, config), vm);
    }
    catch(...){
        std::cout << "Error : parameters non defined\n";
        return;
    }

    po::notify(vm);

    //print help messages
    if(vm.count("help") ){
        std::cout << config << std::endl;
        return;
    }
}

