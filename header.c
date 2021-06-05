#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mount.c"
#include "parseRequest.c"
char Content_Type[][20] = {
    "text/html",
    "text/plain", 
    "image/gif", 
    "image/jpeg", 
    "image/png"
};

/* char _StatusOK[2000] = "HTTP/1.1 200 OK\nContent-Type:text/plain\nContent-Length:12\n\nHello world!";
 */
/* default method: GET default path: root path*/
#define INDEX "/index.html"
int get_file_path(char * path, char * relative_path) {
    strcat(path, mount_path);
    strcat(path, relative_path);
    printf("mount_path %s relative_path %s path %s\n", mount_path, relative_path, path);
    char file_type_name[20] = {0};
    int ptr = 0;
    int i = 0;
    while(relative_path[i] == '.') {
        ptr = i; i++;
    }
    strcpy(file_type_name, &relative_path[ptr+1]);
    if(strcmp(file_type_name, "html")) {
        return 0;
    }else if(strcmp(file_type_name, "txt")) {
        return 1;
    }else if(strcmp(file_type_name, "gif")) {
        return 2;
    }else if(strcmp(file_type_name, "jpeg")) {
        return 3;
    }else if(strcmp(file_type_name, "png")) {
        return 4;
    }
}

int read_file(const char * path, char * html_buffer) {
    int ptr = 0;
    FILE * fp = fopen(path, "r");
    printf("file path: %s\n", path);
    
    if(fp != NULL) {
        while(!feof(fp)) {
            html_buffer[ptr++] = fgetc(fp);
        }
        html_buffer[ptr - 1] = 0;
        fclose(fp);
    }else {
        printf("failed to open the file!\n");
        // memset(buf, 0, sizeof(buf));
        return 404;
    }
    return 200;
}

void get_content_length(char * content_length, char * content_buffer) {
    sprintf(content_length, "%d", strlen(content_buffer));
}

const char * generate_header(char http_method, const char * relative_path, const char * raw_request) {
    static char buf[3000] = {0};
    memset(buf, 0, sizeof(buf));
    strcat(buf, "HTTP/1.1 ");
    // int result = search_through_path(relative_path);
    // int result = 200;
    struct Request * request = parseRequest((const char *)raw_request);
    
    char path[50] = {0};
    int my_file_type = get_file_path(path, request->relative_path);

    char html_buffer[2000] = {0};
    memset(html_buffer, 0, sizeof(html_buffer));
    int result = read_file(path, html_buffer);

    switch(result) {
        case 200:
            strcat(buf, "200 ok\n");
            break;
        case 404:
            strcat(buf, "404 Not Found\n");
            strcat(buf, "Content-Type: text/html");
            return buf;
        case 400:
        default: 
    }
    strcat(buf, "Content-Type: ");
    strcat(buf, Content_Type[my_file_type]);
    strcat(buf, "\n");

    printf("path: %s\n", path);
    int ptr = 0;
    // memset(path, 0, sizeof(path));
    // strcpy(path, "/home/ccrr/http-server/root/index.html");

    char content_length[10] = {0};
    // itoa(ptr, content_length, 10);
    // sprintf(content_length, "%d", ptr);
    strcat(buf, "Content-Length: ");
    strcat(buf, content_length);
    strcat(buf, "\n\n");
    strcat(buf, html_buffer); 
    printf("html buffer:\n%s\n", buf);
    return buf;
}