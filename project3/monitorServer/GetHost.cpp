#include "Interface.h"
#include <cstring>

// Assistant functions
void perror_exit(string message, int line)
{
    perror(message.c_str());
    cout << "Error at GetHost.cpp in line " << line << endl;
    exit(EXIT_FAILURE);
}

// connecting clients to the socket given in the port given
// returns the new socket created for data transportation between the server and the client
int listening_to_connections(int sock, int port)
{
    struct sockaddr_in server, client;
    socklen_t clientlen;

    struct sockaddr *serverptr=(struct sockaddr *)&server;
    struct sockaddr *clientptr=(struct sockaddr *)&client;

    server.sin_family = AF_INET;       /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);      /* The given port */
    /* Bind socket to address */
    if (bind(sock, serverptr, sizeof(server)) < 0)
        perror_exit("bind", 24);
    /* Listen for connections */
    if (listen(sock, 5) < 0) perror_exit("listen", 27);
    printf("Listening for connections to port %d\n", port);
    int newsock;
    /* accept connection */
    if ((newsock = accept(sock, clientptr, &clientlen)) < 0) perror_exit("accept", 31);

    printf("Accepted connection\n");
    return newsock;
}