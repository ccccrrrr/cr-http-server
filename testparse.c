#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.c"


int main() {
/*
    // struct Request * request = parseRequest("GET /index.html   ");
    // printf("%d %s", request->method, request->relative_path);
*/
    const char * header = generate_header(200, "/index.html", "GET /home/picture.png HTTP/1.1");
    printf("%s\n", header);

    return 0;
}