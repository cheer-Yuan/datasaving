# ReadMe

This is a primitive version of recording intel LiDAR data to local, using realsense2 c++ API.

Reference : https://github.com/IntelRealSense/librealsense/tree/master/examples

## Examples for parameters

### To record 3 groups of data, one every 10 seconds, record all files including point cloud .ply, together with the rgb, depth and infrared photos):

./datasaving -n 3 -i 10 

### To record in infinite mode, no waiting time between 2 records, using the resolution of 424\*240, and recording JUST the PLY files

./datasaving -n -1 -i 0 -f 0 -r 0 -d 0 -l 6

## Reinstall the INTEL realsense library :

Navigate to librealsense root directory

```sh
mkdir build && cd build
```

```sh
cmake ../ -DCMAKE_BUILD_TYPE=Release
```

```sh
sudo make uninstall && make clean && make && sudo make install
```

## Reinstall the INTEL realsense library for raspbian:

Navigate to librealsense root directory

```sh
mkdir build && cd build
```

```sh
cmake .. -DBUILD_EXAMPLES=true -DCMAKE_BUILD_TYPE=Release -DFORCE_LIBUVC=true
```

```sh
make -j1
```

```sh
sudo make uninstall && make clean && make && sudo make install
```

## Usage

```sh
$ cmake .
```

```sh
$ make
```

```sh
./datasaving -n -1 -i 10 
```

```sh
$ chmod 777 monitorProcess.sh
```

```sh
./monitorProcess.sh
```

## Parameters 

-n : Numbers of data to record, use -1 to launch an endless record. Default value = -1,

-i : Time period in which we make one record, default value = 0

-p : Use 1 to record point cloud .ply file and 0 to skip it, default value = 1

-r : Use 1 to record real rgb photo and 0 to skip it, default value = 1

-d : Use 1 to record photo colored by the depth and 0 to skip it, default value = 1

-f : Use 1 to record infrared photo and 0 to skip it, default value = 1

-l : 

For L515 :

    Use 1 to record .ply files in the highest reslution of 1024\*768

    Use 2 to record .ply files in a medium resolution of 640\*480 (default mode)

    Use 3 to record .ply files in the lowest resolution of 320\*240 in order to save the time and gain a faster data processing.

For D455 :

    Use 4 to record .ply files in the highest reslution of 1280\*720

    Use 5 to record .ply files in a medium resolution of 848\*480

    Use 6 to record .ply files in the lowest resolution of 424\*240 in order to save the time and gain a faster data processing. 

-c : Use 0 to record the .ply files without colors and 1 to record the .ply files with colors, default value = 0.

### Version 1.5

Now support the lowerd resolution 424\*240 (FOR D455) for the point cloud files, which saves more time. 

A brief benchmark on the resolution 424\*240 and .ply files only, platform : LINUX 5.4.0, cpu: Intel(R) Core(TM) i5-1035G7 CPU @ 1.20GHz, stockage NVME SSD

Saving bandwidth :  24.3Mb / s , which is about 7 .ply files per second.

### Version 1.4

Now support the fast saving mode : save the .ply files without colors will be faster

### Version 1.3

Time interval is more accurate now : it calculates the time to halt according to the time spent on the las record

All designed parameters are now supported, choose any type of data to be recorded

Continuous record time is shortened to 2 seconds / entire group of data  

### Version 1.2

monitorProcess.sh : a bash program which overlooks the process of datasaving and restarts it when face a crash (Linux)

use chmod command to give the needed authority

time for saving 1 group of data : 6 - 7 seconds

the line of code which makes the program wait for 30 frames is now deleted, but almost no influence on the time a

### Version 1.1 :

Parameters' Values :
-n : Any value, use -1 to lance an infinite loop.
-i : > 10, according to the cpu and stockage
### Version 1.0 :

Specify the parameters :
-n : total number of picture groups
-i : interval between 2 groups
### Version 0.1 :

Saving a videoclip under the .bag format
### Version 0.0 : 

Saving a dotcloud to a .ply file.