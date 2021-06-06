#include <stdio.h>
#include <string.h>

extern const char mount_path[50];

/* default method: GET default path: root path*/
#define INDEX "/index.html"
// get_file_path return file type
int get_file_path(char * path, char * relative_path) {
    strcat(path, relative_path);
    // printf("mount_path %s relative_path %s path %s\n", mount_path, relative_path, path);
    char file_type_name[20] = {0};
    int ptr = 0;
    int i = 0;
    while(relative_path[i] != 0) {
        if(relative_path[i] == '.') {
            ptr = i;
        }
        i++;
    }
    strcpy(file_type_name, &relative_path[ptr + 1]);
    printf("file_type_name: %s\n", file_type_name);

    if(strcmp(file_type_name, "html") == 0) {
        return 0;
    }else if(strcmp(file_type_name, "txt") == 0) {
        return 1;
    }else if(strcmp(file_type_name, "gif") == 0) {
        return 2;
    }else if(strcmp(file_type_name, "jpeg") == 0) {
        return 3;
    }else if(strcmp(file_type_name, "png") == 0) {
        return 4;
    }
}

int read_file(const char * path, char * file_buffer) {
    int ptr = 0;
    FILE * fp = fopen(path, "r");
    // printf("file path: %s\n", path);

    if(fp != NULL) {
        while(!feof(fp)) {
            file_buffer[ptr++] = fgetc(fp);
        }
        file_buffer[ptr - 1] = 0;
        fclose(fp);
    } else {
        printf("failed to open the file!\n");
        // memset(buf, 0, sizeof(buf));
        return 404;
    }
    return 200;
}

void get_file(struct Request * request, struct file_reader * reader) {
    char path[50] = {0};
    reader->type = get_file_path(path, request->relative_path);

    memset(reader->content, 0, sizeof(reader->content));
    reader->result = read_file(path, reader->content);
}

void method_get(struct Request *request, struct Response * response) {
    response->method = METHOD_GET;
    strcpy(response->protocal, request->protocal);

    printf("path: %s\n", request->relative_path);
    FILE * fp = fopen(request->relative_path, "r");
    if(fp == NULL) {
        response->return_status = 404;
        return;
    }else {
        fclose(fp);
        response->return_status = 200;
        get_file(request, response->file);
//        fclose(fp);
    }
}

void method_post(struct Request *request, struct Response * response, char * content) {
    response->method = METHOD_POST;
    strcpy(response->protocal, request->protocal);

    FILE * fp = fopen(request->relative_path, "w");

    fprintf(fp,"%s", content);
    fclose(fp);

}

void method_delete(struct Request *request, struct Response * response) {

}

void method_undefined(struct Request *request, struct Response * response) {

}
