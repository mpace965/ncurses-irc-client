#include <ncurses.h>
#include <string.h>

#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "../globals.h"
#include "ModelDriver.h"

ModelDriver::ModelDriver(bool * run)
{
    running = run;
    selectedFirstRunButton = FRUSER;
    addUserAttempt = USERNOTATTEMPTED;

    selectedWindow = CHATWINDOW;
    userHighlighted = 0;
    userPage = 0;

    roomHighlighted = 0;
    roomPage = 0;
    selectedRoom = "";

    topMsg = 0;
    botMsg = 0;

    username = "";
    password = "";
    host = "";
    sport = "";
    port = 0;

    lastUpdated = 0;

    for (int i = 0; i < 40; i++) {
        char name[20];
        gen_random(name, 20);
        addUser(strdup(name));
    }

    /*
    for (int i = 0; i < 40; i++) {
        char name[20];
        gen_random(name, 20);
        addRoom(strdup(name));
    }
    */

    for (int i = 0; i < 100; i++) {
        char msg[50];
        gen_random(msg, 50);
        addMsg(strdup(msg));
    }
}

ModelDriver::~ModelDriver()
{

}

void ModelDriver::updateFirstRun()
{

}

void ModelDriver::update()
{
    if (((int) time(NULL) - lastUpdated > 5)) {
        char response[MAX_RESPONSE];
        sendCommand("LIST-ROOMS", "", response);
        digestRooms(response);

        lastUpdated = (int) time(NULL);
    }
}

void ModelDriver::badUser()
{
    *running = false;
    fprintf(stderr, "Bad authentication.");
}

void ModelDriver::digestRooms(char * roomList)
{
    rooms.clear();
    char * split;
    split = strtok(roomList, "\r\n");
    addRoom(split);

    while ((split = strtok(NULL, "\r\n")) != NULL)
        addRoom(strdup(split));
}

int ModelDriver::getRoomIndexByName(const char * name)
{
    int index;
    int size = getNumRooms();

    for (index = 0; index++ < size; index++)
        if (!strcmp(name, getRoom(index)))
            break;

    return index;
}

int ModelDriver::sendCommand(const char * command, const char * args, char * response)
{
    int sock = open_client_socket();

    // Send command
    write(sock, command, strlen(command));
    write(sock, " ", 1);
    write(sock, username, strlen(username));
    write(sock, " ", 1);
    write(sock, password, strlen(password));
    write(sock, " ", 1);
    write(sock, args, strlen(args));
    write(sock, "\r\n",2);

    // Keep reading until connection is closed or MAX_RESPONSE
    int n = 0;
    int len = 0;
    while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
        len += n;
    }

    response[len] = '\0';

    //printf("response:%s\n", response);

    close(sock);

    if (!strcmp(response, WRONGPWMSG))
        badUser();
}

int ModelDriver::open_client_socket()
{
    // Initialize socket address structure
    struct  sockaddr_in socketAddress;

    // Clear sockaddr structure
    memset((char *)&socketAddress,0,sizeof(socketAddress));

    // Set family to Internet 
    socketAddress.sin_family = AF_INET;

    // Set port
    socketAddress.sin_port = htons((u_short)port);

    // Get host table entry for this host
    struct  hostent  *ptrh = gethostbyname(host);
    if ( ptrh == NULL ) {
        perror("gethostbyname");
        exit(1);
    }

    // Copy the host ip address to socket address structure
    memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);

    // Get TCP transport protocol entry
    struct  protoent *ptrp = getprotobyname("tcp");
    if ( ptrp == NULL ) {
        perror("getprotobyname");
        exit(1);
    }

    // Create a tcp socket
    int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    // Connect the socket to the specified server
    if (connect(sock, (struct sockaddr *)&socketAddress,
                sizeof(socketAddress)) < 0) {
        perror("connect");
        exit(1);
    }

    return sock;
}

