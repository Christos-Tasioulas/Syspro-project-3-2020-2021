#include <iostream>
#include <cstdlib>
#include "Handle.h"

int main(int argc, char* argv[])
{
    if(argc != 13)
    {
        cout << "Wrong number of arguments" << endl;
        exit(EXIT_FAILURE);
    }

    // this are the variables we will use instead of the argv array
    int numMonitors = 0;
    int socketBufferSize = 0;
    int cyclicBufferSize = 0;
    int sizeOfBloom = 0;
    string input_dir = "";
    int numThreads = 0;

    // checking the order and the validity of the run command we give from the makefile
    for(int index = 1; index <= 11; index=index+2)
    {
        string argument = argv[index];
        if(argument == "-m")
        {
            // we won't define any of the 6 variables more than once in the program
            if(numMonitors == 0) numMonitors = atoi(argv[index+1]);
            else
            {
                cout << "Invalid Argument" << endl;
                return -1;
            } 
        }
        else if(argument == "-b")
        {
            // we won't define any of the 6 variables more than once in the program
            if(socketBufferSize == 0) socketBufferSize = atoi(argv[index+1]);
            else
            {
                cout << "Invalid Argument" << endl;
                return -1;
            }

        }
        else if(argument == "-c")
        {
            // we won't define any of the 6 variables more than once in the program
            if(cyclicBufferSize == 0) cyclicBufferSize = atoi(argv[index+1]);
            else
            {
                cout << "Invalid Argument" << endl;
                return -1;
            }

        }
        else if(argument == "-s")
        {
            // we won't define any of the 6 variables more than once in the program
            if(sizeOfBloom == 0) sizeOfBloom = atoi(argv[index+1]);
            else
            {
                cout << "Invalid Argument" << endl;
                return -1;
            }

        }
        else if(argument == "-i")
        {
            // we won't define any of the 6 variables more than once in the program
            if(input_dir == "") input_dir = argv[index+1];
            else
            {
                cout << "Invalid Argument" << endl;
                return -1;
            }

        }
        else if(argument == "-t")
        {
            // we won't define any of the 6 variables more than once in the program
            if(numThreads == 0) numThreads = atoi(argv[index+1]);
            else
            {
                cout << "Invalid Argument" << endl;
                return -1;
            }

        }
        // only these 6 string values are valid for those indexes
        else 
        {
            cout << "Invalid Argument" << endl;
            return -1;
        }
        
    }

    int line = handle(numMonitors, socketBufferSize, cyclicBufferSize, sizeOfBloom, input_dir, numThreads);
    if(line)
    {
        cout << "Error at line " << line << endl;
        exit(EXIT_FAILURE);
    }

    return 0;

}