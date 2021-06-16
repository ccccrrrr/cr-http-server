//
// Created by ccrr on 6/16/21.
//
#include <string.h>
#include <stdio.h>
#include "header.h"
#include "util/concat.c"


void convert_post_response_to_buffer(struct Response  * response, char * recv_buffer) {
    strcat(recv_buffer, response->protocal);

    switch(response->return_status) {
        case 200:
            strcat(recv_buffer, " 200 OK\r\n");
            if(response->file->result == 404)
                return;
            strcat(recv_buffer, "Content-Type: text/plain\r\n");

            char content_length[50] = {0};
//            get_content_length(content_length, strlen(POST_SUCCESS));
            sprintf(content_length, "%lu", strlen(POST_SUCCESS));

            strcat(recv_buffer, "Content-Length: ");
            strcat(recv_buffer, content_length);
            strcat(recv_buffer, "\r\n\r\n");
            strcat(recv_buffer, POST_SUCCESS);
            printf("recv_buffer:\n%s", recv_buffer);
            break;
        case 404:
            strcat(recv_buffer, " 200 ok\r\nContent-Type: text/plain\r\n\r\n");
            strcat(recv_buffer, PATH_NOT_FOUND);
            return;
        case 400:
            break;
        default: break;
    }
}


void convert_delete_response_to_buffer(struct Response * response, char * recv_buffer) {
    strcat(recv_buffer, response->protocal);
    strcat(recv_buffer, " ");

    switch (response->return_status) {
        case 200:
            strcat(recv_buffer, "200 OK\r\n");
            strcat(recv_buffer, "Content-Type:text/plain\r\n\r\n");
            strcat(recv_buffer, DELETE_SUCCESS);
            break;
        case 404:
            // should also be 200 OK?
            strcat(recv_buffer, "404 Not Found\r\n");
            strcat(recv_buffer, "Content-Type:text/plain\r\n\r\n");
            strcat(recv_buffer, DELETE_FAIL);
            break;
        case 400:
            break;
    }
}

int convert_get_response_to_buffer(struct Response * response, char * recv_buffer) {
    strcat(recv_buffer, response->protocal);

    switch(response->return_status) {
        case 200:
            concat_status(recv_buffer, response->file->result);
            if(response->file->result == 404)
                return 0;

            concat_type(recv_buffer, response->file->type);
            int ptr = 0;

            char content_length[10] = {0};
            sprintf(content_length, "%d", response->file->length);
            strcat(recv_buffer, "Content-Length: ");
            strcat(recv_buffer, content_length);
            strcat(recv_buffer, "\r\n\r\n");
            strcat(recv_buffer, response->file->content);
            int length = strlen(recv_buffer);
            printf("buffer:\n%s\n", recv_buffer);

            return 0;
        case 404:
            strcat(recv_buffer, " 404 Not Found\r\n");
            strcat(recv_buffer, "Content-Type: text/plain\r\n");
            strcat(recv_buffer, "Content-Length: 35\r\n\r\n");
            strcat(recv_buffer, GET_FAIL);
            return 0;
        case 400:
            break;
        default: break;
    }
    return 0;
}


