#include <stdio.h>
#include <stdlib.h>

#define METHOD_GET 0
#define METHOD_POST 1
#define METHOD_DELETE 2

struct file_reader {
    int type;
    char content[2000];
    int result;
};

struct Response {
    int method;
    int return_status;
    char protocal[20];
    char content[2000];
    struct file_reader * file;
};

struct Request {
    int method;
    char relative_path[100];
    char protocal[20];
};