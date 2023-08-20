#include <iostream>
#include <cstring>
#include "Handle.h"
#include "Interface.h"

// function to print directories
void visit_directory(void* n)
{
    string name = *((string*) n);
    cout << name;
}

// visiting a virus bloom filter to print
void visit_virus_bloom(void *my_virus_bloom)
{ 
    VirusBloom *vb = (VirusBloom *) my_virus_bloom;
    cout << vb->get_virus_name() << endl;
    vb->get_bloom_filter()->Print();
}

// function that updates the list of bloomfilters with bloomfilters
int receive_bloomfilters(List* virus_bloom_list, int sock, int sizeOfBloom)
{
    while(1)
    {
        char* c_virus = read_string(sock);
        if(c_virus == NULL)
        {
            cout << "Error reading the socket" << endl;
            return 27;
        }

        if(!strcmp(c_virus, "No more bloomfilters")) break;

        string virus(c_virus);

        BloomFilter* bf = virus_has_a_bloom_filter(virus, virus_bloom_list);
        if(bf == NULL)
        {
            VirusBloom* vb = new VirusBloom(virus, sizeOfBloom);
            bf = vb->get_bloom_filter();
            virus_bloom_list->ListInsertLast(vb);
        }
        
        unsigned char* bloom_array = read_bloom(sock, sizeOfBloom);
        if(bloom_array == NULL)
        {
            cout << "Error reading the socket" << endl;
            return 46;
        }
        
        bf->set_array(bloom_array);
    }
    return 0;
}

// Takes control of the program after working with the run command arguments in the main function
// Returns the line an error occured or 0 if it worked properly
int handle(int numMonitors, int socketBufferSize, int cyclicBufferSize, int sizeOfBloom, string input_dir, int numThreads)
{
    string up = "../";
    List* directory_list = directory_sorting(up.append(input_dir)); 
    //directory_list->print(visit_directory);

    // Creating the children
    pid_t* child_processes;
    child_processes = child_creation(numMonitors, socketBufferSize, cyclicBufferSize, sizeOfBloom, numThreads, directory_list);

    // Error checking for the children
    if(child_processes == NULL)
    {
        cout << "Error creating children!" << endl;
        return 68;
    }

    // creating the sockets 
    int* socks = create_sockets(numMonitors);

    if(socks == NULL)
    {
        cout << "Error creating sockets" << endl;
        return 78;
    }

    struct hostent* host = get_host();
    string ip = get_ip(host, 0);

    int port = STARTER_PORT;
    for(int i=0; i<numMonitors; i++)
    {
        connect_to_server(socks[i], port, host);
        port++;
    }

    List* virus_bloom_list = new List();

    for(int i = 0; i<numMonitors; i++)
    {
        int rb = receive_bloomfilters(virus_bloom_list, socks[i], sizeOfBloom);
        if(rb != 0)
        {
            return rb;
        }
    }

    List* travel_request_list = new List();

    cout << "Type: /<command> <arguments>" << endl;
    string input;
    getline(cin, input);
    while(input != "/exit")
    {
        input_manager(input, travel_request_list, virus_bloom_list, sizeOfBloom, socks, numMonitors);
        getline(cin, input);
    }
    // sending the /exit command to the child process
    for(int i=0; i<numMonitors; i++)
    {
        if(write_string(socks[i], input) == false)
        {
            cout << "Error writing at the socket" << endl;
            return 117;
        }
    }

    // Waiting for the child proccesses to finish
    bool wait = child_waiting(child_processes, numMonitors);

    // Error checking the waiting function
    if(wait == false)
    {
        cout << "Error waiting the child processes" << endl;
        return 125;
    }

    destroy_travel_requests_list(travel_request_list);
    list_destroy_directories(directory_list);
    destroy_virus_bloom_list(virus_bloom_list);
    close_sockets(socks, numMonitors);
    delete[] socks;

    return 0;
}