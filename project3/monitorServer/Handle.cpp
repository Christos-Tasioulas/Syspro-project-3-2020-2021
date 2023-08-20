#include <iostream>
#include <cstring>
#include "Handle.h"
#include "Interface.h"

// Assistant functions

// visiting a citizen to print
void visit_citizen(void *my_citizen)
{ 
    CitizenRecord *c = (CitizenRecord *) my_citizen;
    c->print();
}

// visiting an id from the citizen record given
void visit_id(void *cr)
{
    CitizenRecord* CR = (CitizenRecord*) cr; 
    string id = CR->get_id();
    cout << id;
}

// visiting a virus bloom filter to print
void visit_virus_bloom(void *my_virus_bloom)
{ 
    VirusBloom *vb = (VirusBloom *) my_virus_bloom;
    cout << vb->get_virus_name() << endl;
    vb->get_bloom_filter()->Print();
}

// visiting a virus bloom filter to print
void visit_virus_skip(void *my_virus_skip)
{ 
    VirusSkip *vs = (VirusSkip *) my_virus_skip;
    cout << vs->get_virusname() << endl;
    if(vs->get_vaccination_state() == true) cout << "Vaccinated People IDs:" << endl;
    else cout << "Not Vaccinated People IDs:" << endl;
    vs->get_skip_list()->Print(visit_id);
}

// function to print directories
void visit_directory(void* n)
{
    string name = *((string*) n);
    cout << name;
}

List* separate_paths(string path_array)
{
    List* paths = new List();

    char* path = new char[path_array.length() + 1];
    strcpy(path, path_array.c_str());

    char* cs;
    cs = strtok(path, " ");

    while(1)
    {
        string* temp = new string(cs);
        paths->ListInsertLast(temp);
        cs = strtok(NULL, " ");
        if(cs == NULL)
        {
            break;
        }
    }

    return paths;
}

// sends bloomfilters to the client via the socket given
int send_bloomfilters(List* virus_bloom_list, int new_sock, int sizeOfBloom)
{
    ListNode* node = virus_bloom_list->get_first();
    while(node != NULL)
    {
        VirusBloom* vb = (VirusBloom *) node->get_value();

        string virus = vb->get_virus_name();

        if(write_string(new_sock, virus) == false)
        {
            cout << "Error at writing to the socket" << endl;
            return 82;
        }

        BloomFilter* bf = vb->get_bloom_filter();
        unsigned char* bloom_array = bf->get_array();

        if(write_bloom(new_sock, bloom_array, sizeOfBloom) ==  false)
        {
            cout << "Error at writing to the socket" << endl;
            return 91; 
        }

        node = node->get_next();
    }

    if(write_string(new_sock, "No more bloomfilters") == false)
    {
        cout << "Error at writing to the socket" << endl;
        return 100;
    }

    return 0;
}

// Takes control of the program after working with the run command arguments in the main function
// Returns the line an error occured or 0 if it worked properly
int handle(int port, int socketBufferSize, int cyclicBufferSize, int sizeOfBloom, string path_array, int numThreads)
{
    List* paths = separate_paths(path_array);

    // paths->print(visit_directory);

    // creating the socket
    int sock = create_socket();
    if(sock == -1)
    {
        cout << "Error creating the socket" << endl;
        return 118;
    }

    int new_sock = listening_to_connections(sock, port);

    List* files = open_directories(paths); 
    if( files == NULL )
    {
        cout << "Error opening the subdirectories" << endl;
        return 127;
    }

    // this is the class we will have every data structure the server needs
    Stats* s = new Stats(cyclicBufferSize, sizeOfBloom);    

    pthread_t* threads = threads_create(numThreads, s, files);

    if(threads == NULL)
    {
        cout << "Error creating the threads" << endl;
        return 137;
    }

    //List* citizen_list = s->get_citizen_list();
    List* virus_bloom_list = s->get_virus_bloom_list();
    //List* virus_skip_list = s->get_virus_skip_list();
    
    int sb = send_bloomfilters(virus_bloom_list, new_sock, sizeOfBloom);
    if(sb != 0)
    {
        return sb;
    }

    //virus_skip_list->print(visit_virus_skip); 
    //citizen_list->print(visit_citizen);

    // reads commands until /exit appears
    while(1)
    {
        char* c_input = read_string(new_sock);
        if(c_input == NULL)
        {
            cout << "Error reading at the socket" << endl;
            return 161;
        }
        if(!strcmp(c_input, "/exit")) break;
        string input(c_input);
        input_manager(input, s, paths, new_sock);
    }

    List* exits = new List();
    CyclicBuffer* cb = s->get_cyclic_buffer();
    threads_exit(numThreads, cb, exits);

    list_destroy_directories(paths);
    list_destroy_files(files);
    list_destroy_files(exits);

    // deleting the threads
    destroy_threads(numThreads, threads);

    delete s;
    delete[] threads;

    // closing the connection with the sockets
    close(new_sock);
    close(sock);

    return 0;
}