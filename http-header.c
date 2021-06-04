#include <stdio.h>
#include <string.h>

#define StatusOK 200
#define HTTP_1_1 1

struct header {
    char method;
    char path[50];
};

struct header * convert_string_to_header(const char * __header) {
    struct header * _header = (struct header *)malloc(sizeof(struct header));
    memset(_header, 0, sizeof(struct header));
    char temp[50] = {0};
    int ptr1 = 0;   // point to __header
    int ptr2 = 0;   // point to temp
    while(__header[ptr1] != '0') {
        temp[ptr2] = __header[ptr1];
        ptr1++;ptr2++;
    }
    memset(temp, 0, sizeof(temp));
    ptr2 = 0;
    while(__header[ptr1] != '0') {
        temp[ptr2] = __header[ptr1];
        ptr1++;ptr2++;
    }
    return _header;

}