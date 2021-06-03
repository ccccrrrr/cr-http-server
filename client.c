#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


#define PORT 8080

int main() {
    int client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char hello[30] = "hello! this is client!";
    char buffer[1024] = {0};
    int valread;
    if(client_sockfd < 0) {
        perror("client socket error.");
        return 0;
    }


    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if(connect(client_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect error!\n");
        return 0;
    }
    send(client_sockfd, hello, strlen(hello), 0);
    valread = read(client_sockfd, buffer, sizeof(buffer));
    printf("%s\n", buffer);
    return 0;
}