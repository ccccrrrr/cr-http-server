#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.c"


int main() {
    struct Request request;
    parseRequest("GET /index.html HTTP/1.1", &request);
    printf("\nresult: %d %s %s\n", request.method, request.relative_path, request.protocal);

    // const char * header = generate_header(200, "GET /home/picture.png HTTP/1.1");
    // printf("%s\n", header);

    return 0;
}