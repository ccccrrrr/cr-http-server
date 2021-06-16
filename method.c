#include <stdio.h>
#include <string.h>


/* default method: GET default path: root path*/
#define INDEX "/index.html"
// get_file_path return file type
int get_file_path(char * path, char * relative_path) {
    strcat(path, mount_path);
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
    }else if(strcmp(file_type_name, "md") == 0) {
        return 5;
    }
}

int read_file(const char * path, struct file_reader * reader) {
    int ptr = 0;
    char absolute_path[30] = {0};

    FILE * fp = fopen(path, "r");

    if(fp != NULL) {
        fread(reader->content, 65535, 1, fp);
        for(ptr = 65534; ptr >= 0; ptr--)
            if(reader->content[ptr] != 0)
                break;
        reader->length = ptr + 1;
        fclose(fp);
    } else {
        printf("[get error] failed to open the file!\n");
        return 404;
    }
    return 200;
}

void get_file(struct Request * request, struct file_reader * reader) {
    char path[50] = {0}; // this is absolute path
    reader->type = get_file_path(path, request->relative_path);

    memset(reader->content, 0, sizeof(reader->content));
    reader->result = read_file(path, reader);
}

void method_get(struct Request *request, struct Response * response) {
    response->method = METHOD_GET;
    strcpy(response->protocal, request->protocal);
    char absolute_path[100] = {0};
    strcat(absolute_path, mount_path);
    strcat(absolute_path, request->relative_path);
//    printf("path: %s\n", request->relative_path);
    FILE * fp = fopen(absolute_path, "r");
    if(fp == NULL) {
        response->return_status = 404;
        return;
    }else {
        fclose(fp);
        response->return_status = 200;
        get_file(request, response->file);
    }
}


void method_post(struct Request *request, struct Response * response, char * content) {
    response->method = METHOD_POST;
    strcpy(response->protocal, request->protocal);

    char absolute_path[100] = {0};
    strcat(absolute_path, mount_path);
    strcat(absolute_path, request->relative_path);

//    FILE * fp = fopen(request->relative_path, "w");
    FILE * fp = fopen(absolute_path, "w");

    if(fp == NULL) {
        response->return_status = 404;
    }else {
        response->return_status = 200;
        fwrite(content, sizeof(content), 1, fp);
        fclose(fp);
    }
}

void method_delete(struct Request *request, struct Response * response) {
    response->method = METHOD_DELETE;
    strcpy(response->protocal, request->protocal);
    char absolute_path[100] = {0};
    strcat(absolute_path, mount_path);
    strcat(absolute_path, request->relative_path);
//    if(remove(request->relative_path) == 0) {
    if(remove(absolute_path) == 0) {
        printf("successfully removed!\n");
        response->return_status = 200;
    } else {
        printf("file not found!\n");
        response->return_status = 404;
    }
}

void method_undefined(struct Request *request, struct Response * response) {

}
