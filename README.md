# ReadMe

This is a primitive version of recording intel LiDAR data to local, using realsense2 c++ API.

Reference : https://github.com/IntelRealSense/librealsense/tree/master/examples

# Examples for parameters

## To record 3 groups of data, one every 10 seconds, record all files including point cloud .ply, together with the rgb, depth and infrared photos):

./datasaving -n 3 -i 10 

## To record in infinite mode, recording JUST the PLY file : (record a group of data every 5 seconds until a manuel exit):

./datasaving -n 5 -i -1 -f 0 -r 0 -d 0


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

-n : Numbers of datas to record, default value = 1, use -1 to launch an endless record

-i : Time period in which we make one record, default value = 10

-p : Use 1 to record the point cloud .ply file and 0 to skip it, default value = 1

-r : Use 1 to record the real rgb photo and 0 to skip it, default value = 1

-d : Use 1 to record the photo colored by the depth and 0 to skip it, default value = 1

-f : Use 1 to record the infrared photo and 0 to skip it, default value = 1

## Version 1.4

Now support the fast saving mode : save the .ply files without colors will be faster

## Version 1.3

Time interval is more accurate now : it calculates the time to halt according to the time spent on the las record

All designed parameters are now supported, choose any type of data to be recorded

Continuous record time is shortened to 2 seconds / entire group of data  
## Version 1.2

monitorProcess.sh : a bash program which overlooks the process of datasaving and restarts it when face a crash (Linux)

use chmod command to give the needed authority

time for saving 1 group of data : 6 - 7 seconds

the line of code which makes the program wait for 30 frames is now deleted, but almost no influence on the time a

## Version 1.1 :

Parameters' Values :
-n : Any value, use -1 to lance an infinite loop.
-i : > 10, according to the cpu and stockage
## Version 1.0 :

Specify the parameters :
-n : total number of picture groups
-i : interval between 2 groups
## Version 0.1 :

Saving a videoclip under the .bag format
## Version 0.0 : 

Saving a dotcloud to a .ply file.