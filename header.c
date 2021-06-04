#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mount.c"
/* char _StatusOK[2000] = "HTTP/1.1 200 OK\nContent-Type:text/plain\nContent-Length:12\n\nHello world!";
 */
/* default method: GET default path: root path*/
#define INDEX "/index.html"
const char * generate_header(char http_method, const char * relative_path) {
    static char buf[3000] = {0};
    memset(buf, 0, sizeof(buf));
    strcat(buf, "HTTP/1.1 ");
    // int result = search_through_path(relative_path);
    int result = 200;
    switch(result) {
        case 200:
            strcat(buf, "200 ok\n");
            break;
        case 404:
        case 400:
        default: 
    }
    strcat(buf, "Content-Type: text/html\n");
    char path[50] = {0};
    strcat(path, mount_path);
    strcat(path, relative_path);
    char html_buffer[2000] = {0};
    memset(html_buffer, 0, sizeof(html_buffer));
    printf("path: %s\n", path);
    int ptr = 0;
    // memset(path, 0, sizeof(path));
    // strcpy(path, "/home/ccrr/http-server/root/index.html");
    FILE * fp = fopen(path, "r");
    printf("file path: %s\n", path);
    if(fp != NULL) {
        while(!feof(fp)) {
            html_buffer[ptr++] = fgetc(fp);
        }
    }else {
        printf("failed to open the file!\n");
    }
    html_buffer[ptr - 1] = 0;
    fclose(fp);
    char content_length[10] = {0};
    // itoa(ptr, content_length, 10);
    sprintf(content_length, "%d", ptr);
    strcat(buf, "Content-Length: ");
    strcat(buf, content_length);
    strcat(buf, "\n\n");
    strcat(buf, html_buffer); 
    printf("html buffer:\n%s\n", buf);
    return buf;
}