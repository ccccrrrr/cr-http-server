#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "header.c"
#define PORT 80

#define GET 0
#define PUT 1
#define DELETE 2
const char mount_path[50] = "/home/ccrr/http-server/root";

// char _StatusOK[2000] = "HTTP/1.1 200 OK\nContent-Type:text/plain\nContent-Length:12\n\nHello world!";

int start_listen(int port, struct sockaddr_in * addr) {

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    addr->sin_port = htons(PORT);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("create socket error.\n");
        return 0;
    }

    if(bind(sockfd, (const struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("failure: binding error.\n");
        return 0 ;
    }

    if(listen(sockfd, 3) < 0) {
        perror("listening error.\b");
        return 0;
    }
    return sockfd;

}

void handle_request(int sockfd, struct sockaddr_in * addr) {
    int valread;
    int new_socket;
    int addrlen = sizeof(*addr);
    char c;
    while(1) {
        if((new_socket = accept(sockfd, (struct sockaddr *)addr, (socklen_t *)&addrlen)) < 0) {
            perror("accept error\n");
            close(sockfd);
            return;
        }else {
            int status_ok = 0;
            char buffer[3000] = {0};
            valread = read(new_socket, buffer, 3000);
            printf("%s\n", buffer);
            char recv_buffer[3000] = {0};
            memset(recv_buffer, 0, sizeof(recv_buffer));

            generate_header(buffer, recv_buffer);
            printf("recv header:\n %s\n", recv_buffer);
            write(new_socket, recv_buffer, 3000);
            close(new_socket);
        }
    }
    close(sockfd);
}

int main() {
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(struct sockaddr_in));

    int sockfd = start_listen(PORT, &addr);

    if(sockfd < 0)
        return 0;

    handle_request(sockfd, &addr);

    return 0;
}