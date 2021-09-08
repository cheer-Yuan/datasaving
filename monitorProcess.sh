#!/bin/bash
while true
do
  # find a particular process, excluding this process itself
  ps -ef | grep "datasaving" | grep -v "grep" | grep -v "nautilus"
# compare the returned value with 1 (the process is found or not)
  if [  "$?" -eq 1  ]
  then
    # read all lines in parameters' file into an array
    mapfile data <parameters.txt

    # extract the 2 parameters
    n="${data[0]}"
    i="${data[1]}"

    # check if all works are done
    if [  $n -eq 0  ]
    then
      exit 0
    fi

    # length of the array
    leng=${#data[@]}

    # calculate how many groups of data is there to be saved yet
    if [ $n -ne -1 ]; then n=$((n - leng + 2)); fi

    # restart the process
    (./datasaving -i $i -n $n)
    echo "process restarted"

  else
    echo "process exists"
  fi
  sleep 10
done