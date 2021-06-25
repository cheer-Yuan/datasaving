# ReadMe

This is a primitive version of recording intel LiDAR data to local, using realsense2 c++ API.

Reference : https://github.com/IntelRealSense/librealsense/tree/master/examples

## Examples for parameters

### To record 3 groups of data, one every 10 seconds, record all files including point cloud .ply, together with the rgb, depth and infrared photos):

./datasaving -dir ./output/ -n 3 -i 10 

### To record in infinite mode, no waiting time between 2 records, using the resolution of 424\*240, and recording JUST the PLY files

./datasaving -dir ./output/ -n -1 -i 0 -f 0 -r 0 -d 0 -l 5

## All parameters 

### -dir 

-dir ./output/ : In which folder to save the output files

### -n

Any integer > 0 : Set the total number of files to save

(default) -1 : Set the total number of files to save to infinite

### -i

Any integer > 0 : Make a record every i seconds

(default) 0 : Start immediately the next record as long as the previous end

### -r 

1 : Save the normal RGB photo 

(default) 0 : Do not save the normal RGB photo

### -d

1 : Save the depth RGB photo

(default) 0 : Do not save the depth RGB photo

### -f

1 : Save the infrared photo

(default) 0 : Do not save the infrared photo

### -p

(default) 1 : Save the .ply point cloud file 

0 : Do not save the infrared photo

### -c

1 : Keep the texture information in the .ply file

(default) 0 : Remove the texture information in the .ply file (faster and smaller)

### -l

(default) 0 : Choose the standard resolution for the depth information 

1 : Use the lowest resolution for depth information of 320 * 240, on L515

5 : Use the lowest resolution for depth information of 424 * 240, on D455

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