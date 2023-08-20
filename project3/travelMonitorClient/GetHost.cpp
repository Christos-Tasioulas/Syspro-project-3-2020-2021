#include "Interface.h"
#include <cstring>

// Assistant functions

// calls perror with the message given and exits the program stating in which line the error has occurred
void perror_exit(string message, int line)
{
    perror(message.c_str());
    cout << "Error at GetHost.cpp in line " << line << endl;
    exit(EXIT_FAILURE);
}

// returns information about the host
struct hostent* get_host()
{
    char   name[1024];
    struct 	hostent *mymachine; 

    int host = gethostname(name, 1024);
    if(host == -1)
    {
        perror("gethostname");
        return NULL;
    }

    mymachine=gethostbyname(name);

    if(mymachine == NULL)
    {
        cout << "Could not resolved Name: " << name << endl;
        return NULL;
    }   

    return mymachine;   
}

// returns the <index>th ip address of the host given
string get_ip(struct hostent* host, int index)
{
    struct in_addr **addr_list;
    char symbolicip[50];

    addr_list = (struct in_addr **) host->h_addr_list;
    // turning the ip address into a string
    if(addr_list[index] != NULL)
    {
        strcpy(symbolicip , inet_ntoa(*addr_list[index]) );
        string ip(symbolicip);
        return ip;
    }
    
    // returns a blank string if there is no ip address
    return "";
}

// connects the client socket given in the given port with the given host 
void connect_to_server(int sock, int port, struct hostent* host)
{
    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr*)&server;

    server.sin_family = AF_INET;       /* Internet domain */
    memcpy(&server.sin_addr, host->h_addr_list[0], host->h_length);
    server.sin_port = htons(port);         /* Server port */
    /* Initiate connection */

    // sending the program for a nap in order to be accepted by the child server 
    sleep(3);

    if (connect(sock, serverptr, sizeof(server)) < 0)
    {
        perror_exit("connect", 63);
    }
	   
}