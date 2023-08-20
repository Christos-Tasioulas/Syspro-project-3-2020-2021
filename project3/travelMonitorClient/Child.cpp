#include "Interface.h"
#include <sys/wait.h>
#include <unistd.h>
#include <string>

// Assisstant functions

// returns an array with strings that have directory paths
string* path_texts(int numMonitors, List* directory_list)
{
    string* paths_array = new string[numMonitors];
    for(int i = 0; i < numMonitors; i++)
    {
        paths_array[i] = "";
    }

    ListNode* node = directory_list->get_first();
    int index=0;

    while(node != NULL)
    {
        string directory = *((string *) node->get_value());
        paths_array[index].append(directory); 
        paths_array[index].append(" ");
        index++;
        if(index >= numMonitors) index = 0;
        node = node->get_next();
    }

    return paths_array;
}

// Creates as many child processes as given
// Returns an array of the child processes' id
pid_t* child_creation(int numMonitors, int socketBufferSize, int cyclicBufferSize, int sizeOfBloom, int numThreads, List* directory_list)
{
    pid_t* process_ids;
    process_ids = new pid_t[numMonitors];

    int starter_port = STARTER_PORT;
    string* paths_array = path_texts(numMonitors, directory_list);

    for(int monitor=0; monitor<numMonitors; monitor++)
    {
        // forking to create child processes
        process_ids[monitor] = fork();

        string port = to_string(starter_port);
        string threads = to_string(numThreads);
        string sbs = to_string(socketBufferSize);
        string cbs = to_string(cyclicBufferSize);
        string bloom_size = to_string(sizeOfBloom);

        // error checking the process
        if(process_ids[monitor] == -1)
        {
            perror("fork");
            return NULL;
        }
        else if(process_ids[monitor] == 0)
        {
            execl("../monitorServer/monitorServer", "./monitorServer", "-p", port.c_str(), "-t", threads.c_str(), "-b", sbs.c_str(), "-c", cbs.c_str(), "-s", bloom_size.c_str(), paths_array[monitor].c_str(), (char*) NULL);
            perror("execl");
            return NULL;
        }

        starter_port++;
    }

    return process_ids;
}

// Makes the parent wait for the given child processes
// Returns true if everything works properly and false if not
bool child_waiting(pid_t* processes_ids, int numMonitors)
{
    for(int monitor = 0; monitor < numMonitors; monitor++)
    {
        pid_t wait_id = waitpid(processes_ids[monitor], NULL, 0);

        // Error checking the wait function
        if(wait_id == -1)
        {
            perror("waitpid");
            return false;
        }
    }
    return true;
}