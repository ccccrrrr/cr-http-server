#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Request {
    int method;
    char relative_path[20];
};

struct Request * parseRequest(const char * raw_request) {
    struct Request * temp = (struct Request *)malloc(sizeof(struct Request));
    memset(temp, 0, sizeof(struct Request));
    char _temp[20] = {0};
    memset(_temp, 0, sizeof(_temp));
    int ptr1 = 0;
    int ptr2 = 0;
    while(raw_request[ptr1] != ' ') {
        _temp[ptr2++] = raw_request[ptr1];
        ptr1++;
    }
    while(raw_request[ptr1] == ' ') ptr1++;
    // printf("_temp: %s\n", _temp);
    if(strcmp(_temp, "GET") == 0) {
        temp->method = 200; // GET
    }
    memset(_temp, 0, sizeof(_temp));
    ptr2 = 0;
    while(raw_request[ptr1] != ' ') {
        _temp[ptr2++] = raw_request[ptr1];
        ptr1++;
    }
    strcpy(temp->relative_path, _temp);
    return temp;
}