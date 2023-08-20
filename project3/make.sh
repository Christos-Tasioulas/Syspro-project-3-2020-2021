#!/bin/bash

# this bash script compiles the two processes from the different directories simultaneously and with the same commands
count=$#

# checking the number of arguments it should be one or two 
if [[ ($count -gt 2 && $count -lt 1) ]];
then
    echo "Wrong number of arguments"
    exit -1
fi

# "make" command
if [[ ($count -eq 1 && $1 == "make") ]];
then
    cd travelMonitorClient/
    make
    cd ..
    cd monitorServer/
    make
    cd ..
# "make run" command    
elif [[ ($count -eq 2 && $1 == "make" && $2 == "run") ]]
then    
    cd monitorServer/
    make
    cd ..
    cd travelMonitorClient/
    make run
    cd ..
# "make clean" command    
elif [[ ($count -eq 2 && $1 == "make" && $2 == "clean") ]]
then
	
    cd travelMonitorClient/
    make clean 
    cd ..  
    cd monitorServer/
    make clean
    cd ..  
	
# "make valgrind" command    
elif [[ ($count -eq 2 && $1 == "make" && $2 == "valgrind") ]]
then    
    cd monitorServer/
    make
    cd ..
    cd travelMonitorClient/
    make valgrind 
    cd ..    
else
    echo "Invalid arguments"    
fi

