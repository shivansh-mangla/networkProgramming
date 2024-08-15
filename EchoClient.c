#include<sys/types.h>
#include<sys/socket.h>

#include<netdb.h>
#include<stdio.h>
#include<string.h>


int main(int argc, char** argv){
    int sockfd, n;
    char sendline[100];  // A buffer to hold the message being sent to the server.
    char recvline[100];  // A buffer to hold the message being recieved from the server.

    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));  // Clears the servaddr structure to ensure it contains no garbage values.

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr =inet_addr("127.0.0.1");
    // inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    // Connects the client to the server specified by servaddr. This establishes a connection between the client and the server.

    while(1){
        bzero(sendline, 100);
        bzero(recvline, 100);

        fgets(sendline, 100, stdin);
        // Reads input from the user and stores it in the sendline buffer.

        send(sockfd, sendline, strlen(sendline), 0);
        // Sends the contents of sendline to the server.

        recv(sockfd, recvline, 100, 0);
        // Receives the server's response and stores it in recvline.

        printf("%s", recvline);
        // Prints the server's response
    }
}
