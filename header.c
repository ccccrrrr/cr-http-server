#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseRequest.c"
#include "method.c"
char Content_Type[][20] = {
    "text/html",
    "text/plain", 
    "image/gif", 
    "image/jpeg", 
    "image/png"
};

extern const char mount_path[50];

void get_content_length(char * content_length, char * content_buffer) {
    sprintf(content_length, "%d", strlen(content_buffer));
}



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


void convert_response_to_buffer(struct Response * response, char * recv_buffer) {
    strcat(recv_buffer, response->protocal);
    
    switch(response->return_status) {
        case 200:
            concat_status(recv_buffer, response->file->result);
            if(response->file->result == 404)
                return;

            concat_type(recv_buffer, response->file->type);
            // printf("path: %s\n", path);
            int ptr = 0;

            char content_length[10] = {0};
            get_content_length(content_length, response->file->content);

            strcat(recv_buffer, "Content-Length: ");
            strcat(recv_buffer, content_length);
            strcat(recv_buffer, "\n\n");
            strcat(recv_buffer, response->file->content);
            printf("html buffer:\n%s\n", recv_buffer);

            break;
        case 404:
            strcat(recv_buffer, " 404 Not Found\r\n\r\n");
            return;
        case 400:
            break;
        default: break;
    }
    strcat(recv_buffer, response->content);
    return;
}

void read_content(char * content, const char * raw_request) {
    int ptr1 = 0;
    int ptr2 = 0;
    while(1) {
        if (raw_request[ptr2] == '\r' && raw_request[ptr2 + 1] == '\n' && raw_request[ptr2 + 2] == '\r' && raw_request[ptr2 + 3] == '\n')
            break;
        ptr2++;
    }
    ptr2 += 4;
    while(raw_request[ptr2] != 0) {
        content[ptr1++] = raw_request[ptr2];
    }
}

void generate_header(const char * raw_request, char * recv_buffer) {

    struct Request request;
    memset(&request, 0, sizeof(struct Request));
    parseRequest((const char *)raw_request, &request);

    struct Response response;
    response.file = (struct file_reader *)malloc(sizeof(struct file_reader));
    memset(response.file, 0, sizeof(struct file_reader));
    char content[2000] = {0};
    memset(content, 0, sizeof(content));
    switch(request.method) {
        case METHOD_GET:
            method_get(&request, &response);
            break;
        case METHOD_POST:
            read_content(content, raw_request);

            method_post(&request, &response, content);
            break;
        case METHOD_DELETE:
            method_delete(&request, &response);
            break;
        default:
            printf("undefined method.\n");
            method_undefined(&request, &response);
            return;
    }
    if(response.return_status == 404) {
        return;
    }
    memset(recv_buffer, 0, sizeof(*recv_buffer));
    convert_response_to_buffer(&response, recv_buffer);
//    convert_response_to_buffer(recv_buffer, &response);
    // printf("protocal: %s\n", request.protocal);
    // strcat(recv_buffer, request.protocal);

    // struct file_reader file;
    // get_file(&request, &file);

    // concat_status(recv_buffer, file.result);
    // if(file.result == 404)
    //     return;
    
    // concat_type(recv_buffer, file.type);

    // // printf("path: %s\n", path);
    // int ptr = 0;

    // char content_length[10] = {0};
    // get_content_length(content_length, file.content);

    // strcat(recv_buffer, "Content-Length: ");
    // strcat(recv_buffer, content_length);
    // strcat(recv_buffer, "\n\n");
    // strcat(recv_buffer, file.content); 
    // printf("html buffer:\n%s\n", recv_buffer);
}