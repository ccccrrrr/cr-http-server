//
// Created by ccrr on 6/16/21.
//
#include "./Config.h"
#include "string.h"

void concat_status(char * recv_buffer, int result) {
    switch(result) {
        case 200:
            strcat(recv_buffer, " 200 ok\r\n");
            break;
        case 404:
            strcat(recv_buffer, " 404 Not Found\r\n");
            strcat(recv_buffer, "Content-Type: text/html");
            return;
        case 400:
            break;
        default:
            break;
    }
}

void concat_type(char * recv_buffer, int type) {
    strcat(recv_buffer, "Content-Type: ");
    strcat(recv_buffer, Content_Type[type]);
    strcat(recv_buffer, "\n");
}

