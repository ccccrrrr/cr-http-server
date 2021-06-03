#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080

// struct sockaddr_in {
//     short            sin_family;   // e.g. AF_INET
//     unsigned short   sin_port;     // e.g. htons(3490)‏
//     struct in_addr   sin_addr;     // see struct in_addr, below
//     char             sin_zero[8];  // zero this if you want to
// };
// struct in_addr {
//     unsigned long s_addr;  // load with inet_aton()‏
// };

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int valread;
    char hello[100] = "hello!this is server!";
    if(sockfd < 0) {
        perror("create socket error.\n");
        return 0;
    }

    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    memset((char *)&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("failure: binding error.\n");
        return 0 ;
    }

    if(listen(sockfd, 3) < 0) {
        perror("listening error.\b");
        return 0;
    }

    int new_socket;
    while(1) {
        if((new_socket = accept(sockfd, (struct sockaddr *)&addr, (socklen_t *)&addrlen)) < 0) {
            perror("accept error\n");
        }else {
            char buffer[3000] = {0};
            valread = read(new_socket, buffer, 3000);
            printf("%s\n", buffer);
            write(new_socket, hello, strlen(hello));
            close(new_socket);
        }
    }


    return 0;
}