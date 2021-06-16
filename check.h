//
// Created by ccrr on 6/15/21.
//
#include <sys/socket.h>
#include <sys/epoll.h>
#ifndef HTTP_SERVER_2_CHECK_H
#define HTTP_SERVER_2_CHECK_H

//struct epoll_event
//{
//    uint32_t events;	/* Epoll events */
//    epoll_data_t data;	/* User data variable */
//} __EPOLL_PACKED;

//typedef union epoll_data
//{
//    void *ptr;
//    int fd;
//    uint32_t u32;
//    uint64_t u64;
//} epoll_data_t;

void check_epoll_events(struct epoll_event * events, int length) {
    for(int i = 0; i < length; i++) {
        if(events[i].events != 0)
            printf("events: %d fd: %d\n", events[i].events, events[i].data.fd);
    }
}


#endif //HTTP_SERVER_2_CHECK_H
