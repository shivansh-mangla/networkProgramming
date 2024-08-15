#include<sys/types.h>  // Contains definitions for data types used in system calls
#include<sys/socket.h>  // Provides definitions for socket functions and structures
#include<netdb.h>
#include<stdio.h>  // Standard I/O functions, such as printf.
#include<string.h>  // Provides functions for manipulating C strings, such as bzero.


int main(){
    char str[100];  // message string
    int listen_fd, comm_fd;

    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET: Refers to the address family for IPv4.
    // SOCK_STREAM: Indicates that this is a TCP socket
    // 0: The protocol, which is set to 0 to automatically choose the appropriate protocol for TCP.

    bzero(&servaddr, sizeof(servaddr));
    // This function zeroes out the memory for the servaddr structure, ensuring no garbage values are present

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //The server will accept connections on any network interface. 
    // htonl converts the address to network byte order.
    servaddr.sin_port = htons(22000);
    // Sets the port number to 22000. htons converts the port number to network byte order.


    bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    // This binds the socket to the specified IP address and port

    listen(listen_fd, 10);
    // This makes the socket ready to accept incoming connections. 
    // The 10 specifies the backlog, meaning up to 10 connection requests can be queued while the server is busy.


    while(1){

        comm_fd = accept(listen_fd, (struct sockaddr*) NULL,  NULL);
        // Waits for a client to connect. When a connection is accepted, comm_fd is used for communication with the client. 
        // The NULL parameters indicate that the server doesn't care about the client's address

        bzero(str, 100);  // Clears the buffer before receiving data

        recv(comm_fd, str, 100, 0);  // Receives data from the client and stores in str buffer

        printf("Echoing back- %s", str);  // Prints the received message

        send(comm_fd, str, strlen(str), 0);  // Echoes the message back to the client

        close(comm_fd);
        // Closes the connection with the client. After this, the server is ready to accept a new connection.
    }
}