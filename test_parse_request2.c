//
// Created by ccrr on 6/16/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "util/regex.c"
#include <string.h>
#include "header.h"
char buffer[] = "GET /index.html HTTP/1.1\r\nContent-Type: text/plain\r\nConnection: keep-alive\r\nContent-Length:5\r\n\r\nhello!";
int main() {
    struct Request * req = (struct Request *)malloc(sizeof(struct Request));
    parse_header(buffer, (int)strlen(buffer), &req->is_keep_alive, &req->request_length, req->content_type, req->str_method, req->relative_path, req->protocal);
    printf("%d %d %s %s %s %s\n", req->is_keep_alive, req->request_length, req->content_type, req->str_method, req->relative_path, req->protocal);
    return 0;
}
