#ifndef HEADER_H
#define HEADER_H

#define METHOD_GET 0
#define METHOD_POST 1
#define METHOD_DELETE 2
#define METHOD_UNDEFINED 3
struct file_reader {
    int type;
    char content[65535];
    int length;
    int result;
};

struct Response {
    int method;
    int return_status;
    int body_length;
    int response_length;
    char protocal[20];
    char content[65535];
    struct file_reader * file;
};

struct Request {
    int request_length;
    int body_length;
    int method;
    char str_method[20];
    char relative_path[100];
    char protocal[20];
    int is_keep_alive;
    char content_type[30];
};


#endif
