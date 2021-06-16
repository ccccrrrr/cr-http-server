#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <string.h>
#include "header.c"
#include "check.h"
#include "Config.h"
#define GET 0
#define PUT 1
#define DELETE 2


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

int handle_request(int new_socket) {

            char buffer[65535] = {0};

            if(read(new_socket, buffer, 65535) == -1) {
                perror("[read] get stream error");
                return 0;
            }

            printf("%s\n", buffer);
            char recv_buffer[65535] = {0};
            memset(recv_buffer, 0, sizeof(recv_buffer));

            int if_alive = generate_response(buffer, recv_buffer);
            printf("recv header:\n %s\n", recv_buffer);
            write(new_socket, recv_buffer, strlen(recv_buffer));

            return if_alive;
}

void epoll_handle(int listen_sock) {
    int epollfd, nfds, conn_fd, n;

    struct sockaddr_in client_addr[MAX_EVENTS];
    memset(client_addr, 0, MAX_EVENTS * (sizeof(struct sockaddr_in)));
    socklen_t client_length[MAX_EVENTS] = {0};

    if((epollfd = epoll_create1(0)) < 0) {
        perror("epoll create error");
    }

    struct epoll_event ev, events[MAX_EVENTS], conn_ev, awake_ev;

    memset(events, 0, MAX_EVENTS * (sizeof(struct epoll_event)));

    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;

    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
    }

    for(;;) {
        if((nfds = epoll_wait(epollfd, events, MAX_EVENTS, 10)) < 0) {
            perror("epoll wait");
        }

//        check_epoll_events(events, MAX_EVENTS);
//        printf("\n");

        for (n = 0; n < nfds; n++) {

            if (events[n].data.fd == listen_sock) {

                conn_fd = accept(listen_sock, (struct sockaddr *) &client_addr[events[n].data.fd], (socklen_t *)&client_length[events[n].data.fd]);

                if (conn_fd == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                conn_ev.events = EPOLLIN | EPOLLET | EPOLLHUP;
                conn_ev.data.fd = conn_fd;

                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_fd, &conn_ev) == -1) {
                    perror("epoll_ctl: conn_fd");
                    continue;
                }

            } else if((events[n].events & EPOLLHUP) == EPOLLHUP) {
                if(epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd, &events[n]) == -1) {
                    perror("epoll_ctl: delete error");
                }
                close(events[n].data.fd);
                continue;
            }else if((events[n].events & EPOLLIN) == EPOLLIN) {

                int if_keep_alive = handle_request(events[n].data.fd);

                if(if_keep_alive == 0) {
                    awake_ev = events[n];
                    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, awake_ev.data.fd, &awake_ev) == -1) {
                        perror("epoll delete error");
                    }
                    close(events[n].data.fd);
                    printf("close an event.\n");
                }

                continue;
            }
        }
    }
}

int main() {
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(struct sockaddr_in));

    int listen_fd = start_listen(PORT, &addr);

    if(listen_fd < 0) {
        perror("listen error");
        return 0;
    }

    epoll_handle(listen_fd);

    return 0;
}