// This is the file that connects every module with each other
#ifndef INTERFACE
#define INTERFACE
#include <string>
#include "List.h"
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "VirusBloom.h"
#include "TravelRequest.h"

#define STARTER_PORT 6969

// Handle.cpp

// function that updates the list of bloomfilters with bloomfilters
int receive_bloomfilters(List* virus_bloom_list, int sock, int sizeOfBloom);

// Free.cpp

// Destroys the list after releasing all the memory the directories are occupying inside the list
void list_destroy_directories(List* directories);

// destroying everything the given virus-bloom filter list includes
void destroy_virus_bloom_list(List* virus_bloom_list);

// destroying everything the given travel request list includes
void destroy_travel_requests_list(List* travel_request_list);

// Child.cpp

// Creates as many child processes as given
// Returns an array of the child processes' id
pid_t* child_creation(int numMonitors, int socketBufferSize, int cyclicBufferSize, int sizeOfBloom, int numThreads, List* directory_list);

// Makes the parent wait for the given child processes
// Returns true if everything works properly and false if not
bool child_waiting(pid_t* processes_ids, int numMonitors);


// GetHost.cpp

// returns information about the host
struct hostent* get_host();

// returns the <index>th ip address of the host given
string get_ip(struct hostent* host, int index);

// connects the client socket given in the given port with the given host
void connect_to_server(int sock, int port, struct hostent* host);

// Sockets.cpp

// creates given a number of sockets, returns an array of their file descriptors
int* create_sockets(int numMonitors);

// Reads and return the string given from the parent 
char* read_string(int sock);

// the function will write the string object and its length given in the socket given 
bool write_string(int sock, string object);

// reads index by index the bloom filter and stores everything in an array that will be returned eventually
unsigned char* read_bloom(int sock, int bloomsize);

// closes the connection with sockets given
void close_sockets(int* socks, int numMonitors);

// Directory.cpp

// Sorting alphabetically the files or subdirectories included in the drectory given and 
// Returning the list with the items
List* directory_sorting(string input_dir);

// IsValid.cpp

// examining whether the virus given has a bloom filter in the list
BloomFilter* virus_has_a_bloom_filter(string virus, List* virus_bloom_list);

// checks whether the date given is valid
bool date_valid(string date);

// compares two dates
int compare_dates(string date1, string date2);

// InputManager.cpp

// managing the input given from the user
// the lists as arguments are the ones to check the existence and the 
// validity of the arguments given
void input_manager(string input, List* travel_request_list, List* virus_bloom_list, int bloom_size, int* socks, int numMonitors);

#endif