#include <string.h>
#include "header.h"
#include "util/regex.c"

extern const char mount_path[50];
// parse request through raw request buffer
void parseRequest(const char * raw_request, struct Request * req) {

    memset(req, 0, sizeof(struct Request));
    char _temp[20] = {0};
    memset(_temp, 0, sizeof(_temp));
    int ptr1 = 0;
    int ptr2 = 0;
    while(raw_request[ptr1] != ' ' && raw_request[ptr1] != '\r' && raw_request[ptr1] != '\n') {
        _temp[ptr2++] = raw_request[ptr1];
        ptr1++;
    }
    while(raw_request[ptr1] == ' ') ptr1++;
    // printf("_temp: %s\n", _temp);
    if(strcmp(_temp, "GET") == 0) {
        req->method = METHOD_GET; // GET
    }else if(strcmp(_temp, "POST") == 0) {
        req->method = METHOD_POST;
    }else if(strcmp(_temp, "DELETE") == 0) {
        req->method = METHOD_DELETE;
    }
    memset(_temp, 0, sizeof(_temp));
    ptr2 = 0;
    while(raw_request[ptr1] != ' ' && raw_request[ptr1] != '\r' && raw_request[ptr1] != '\n') {
        _temp[ptr2++] = raw_request[ptr1];
        ptr1++;
    }
    strcat(req->relative_path, mount_path);
    strcat(req->relative_path, _temp);
    memset(_temp, 0, 20);
    while(raw_request[ptr1] == ' ' || raw_request[ptr1] == '\r' || raw_request[ptr1] == '\n') ptr1++;
    ptr2 = 0;
    while(raw_request[ptr1] != ' ' && raw_request[ptr1] != '\n' && raw_request[ptr1] != '\r') {
        _temp[ptr2++] = raw_request[ptr1];
        ptr1++;
    }
    strcpy(req->protocal, _temp);
    // printf("request: %s %s", req->relative_path, req->protocal);
}

void parse_request2(const char *raw_request, struct Request * req) {
    parse_header(raw_request, 65535, &req->is_keep_alive, &req->request_length, req->content_type, req->str_method, req->relative_path, req->protocal);
    if(strcmp(req->str_method, "GET") == 0)
        req->method = METHOD_GET;
    else if(strcmp(req->str_method, "POST") == 0)
        req->method = METHOD_POST;
    else if(strcmp(req->str_method, "DELETE") == 0)
        req->method = METHOD_DELETE;
    else
        req->method = METHOD_UNDEFINED;
}