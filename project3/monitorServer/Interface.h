// This is the file that connects every module with each other
#ifndef INTERFACE
#define INTERFACE
#include <string>
#include "List.h"
#include <sys/types.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <cstdio>
// #include <fcntl.h>
// #include <ctype.h>
// #include "CitizenRecord.h"
#include "Stats.h"

// strlen("../input_dir/") = 13
#define PATHLEN 13

// Handle.cpp

// sends bloomfilters to the client via the socket given
int send_bloomfilters(List* virus_bloom_list, int new_sock, int sizeOfBloom);

// Free.cpp

// Destroys the list after releasing all the memory the directories are occupying inside the list
void list_destroy_directories(List* directories);

// destroying everything the given countries stats list includes
// void destroy_country_stats_list(List* country_stats_list);

// destroying everything the given list of filenames includes
void list_destroy_files(List* files);

// Directory.cpp

// Reads and opens all the directories in the given list and their files 
// The names are needed for the countrystats class
// Returns a list with all the files we read
List* open_directories(List* directories_list);

// File.cpp

// Returns the number of lines in the file
int get_file_size(string filename);

// Opens the file given and saves the citizens, bloom filters and skip lists in the lists given
void open_citizen_file(string filename, Stats* s, int bloomsize, int skip_size);


// GetHost.cpp

// connecting clients to the socket given in the port given
// returns the new socket created for data transportation between the server and the client
int listening_to_connections(int sock, int port);

// Sockets.cpp

// Craetes a socket, returns its file descriptor
int create_socket();

// Reads and return the string given from the parent 
char* read_string(int sock);

// the function will write the string object and its length given in the socket given
bool write_string(int sock, string object);

// the function will write the bloom filter given in the socket given
bool write_bloom(int sock, unsigned char* bloom_array, int bloomsize);

// Threads.cpp

// Fills the cyclic buffer with file paths
void producer(CyclicBuffer* cb, List* files);

// creates a given number of threads that call the consumer function with the stats given as an argument
// afterwards it calls the producer function with the stats and list of file paths given as arguments
// returns an array of the threads created
pthread_t* threads_create(int numThreads, Stats* s, List* files);

// Calls the threads to exit their processes using the list of strings given
void threads_exit(int numThreads, CyclicBuffer* cb, List* exits);

// destroys the number of threads given if it exists
void destroy_threads(int numThreads, pthread_t* threads);

// IsValid.cpp

// confirming the record is invalid
void record_error(string* record_array);

// checking whether the given potential record attributes
// are valid according to a given list of citizen records
// returns: 
// >2 if the record is new, 
// >1 if the record already eixsts but not the virus
// >0 if the record is invalid
int is_valid(string* record_array, List* citizen_list);

// checks whether the date given is valid
bool date_valid(string date);

// compares two dates
int compare_dates(string date1, string date2);

// examining whether the virus given has a bloom filter in the list given
// returns the bloomfilter itself if it exists
BloomFilter* virus_has_a_bloom_filter(string virus, List* virus_bloom_list);

// examining whether the virus given has skip lists in the list given
bool virus_has_skip_lists(string virus, List* virus_skip_list);

// examining whether the virus given has a skip list in the list given
// returns the skiplist depending the yesno argument itself if it exists
// if yesno == yes returns the skip list for the vaccinated people
// otherwise returns the skip list for the non vaccinated people
SkipList* virus_has_a_skip_list(string virus, List* virus_skip_list, string yesno);

// testing whether the citizen id given exists in the list given
CitizenRecord* id_exists(string id, List* citizen_list);

// testing whether the citizen has been recorded with the virus given
CitizenVirus* virus_exists(string virus, CitizenRecord* CR);

// returns whether the citizen has been vaccinated or not
bool citizen_is_vaccinated(string virus, CitizenRecord* CR);

// Finding if a country exists by checking a list of paths
bool country_exists(string country, List* paths);

// evaluating if the files on the list are not and removing those that are not
void new_files_evaluation(List* files);

// InputManager.cpp

// managing the input given from the user
// the lists as arguments are the ones to check the existence and the 
// validity of the arguments given
void input_manager(string input, Stats* s, List* paths, int sock);

#endif