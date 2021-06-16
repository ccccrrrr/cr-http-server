//
// Created by ccrr on 6/16/21.
//
#include <stdio.h>
#include "regex.h"
#include <regex.h>
#include <string.h>
#include <stdlib.h>

regex_t reg_connection_struct, reg_content_length_struct, reg_content_type_struct, reg_method_path_protocal_struct;
void init_regex();
void parse_header(const char * raw_buffer, int buffer_length, int * if_keep_alive, int * content_length, char * content_type, char * method, char * path, char * protocal);


void init_regex() {

    int cflags = REG_NEWLINE | REG_EXTENDED;

    regcomp(&reg_connection_struct, reg_connection_pattern, cflags);

    regcomp(&reg_content_length_struct, reg_content_length, cflags);

    regcomp(&reg_content_type_struct, reg_content_type, cflags);

    regcomp(&reg_method_path_protocal_struct, reg_method_path_protocal_pattern, cflags);

}

void parse_header(const char * raw_buffer, int buffer_length, int * if_keep_alive, int * content_length, char * content_type, char * method, char * path, char * protocal) {

    init_regex();

    int status;
    regmatch_t pmatch[4];

    // if keep alive
    status = regexec(&reg_connection_struct, raw_buffer, 2, pmatch, 0);
    if(status == REG_NOMATCH) {
        perror("no connection configuration in header.\n");
        *if_keep_alive = 0;
    } else if(status == 0) {
        *if_keep_alive = strncmp(raw_buffer + pmatch[1].rm_so, "keep-alive", strlen("keep-alive")) == 0 ? 1 : 0;
    }

    // get content-length
    status = regexec(&reg_content_length_struct, raw_buffer, 2, pmatch, 0);
    if(status == REG_NOMATCH) {
        perror("no content length in header.");
        *content_length = 0;
    } else {
        *content_length = (int)strtol(raw_buffer + pmatch[1].rm_so, NULL, 10);
    }

    // get content-type
    status = regexec(&reg_content_type_struct, raw_buffer, 2, pmatch, 0);
    if(status == REG_NOMATCH) {
        printf("[parse request] no content type in header\n");
        strcpy(content_type, "text/plain");
    } else {
        strncpy(content_type, raw_buffer + pmatch[1].rm_so, pmatch[1].rm_eo - pmatch[1].rm_so);
        content_type[strlen(content_type)] = 0;
    }

    // get method, path, and protocol
    status = regexec(&reg_method_path_protocal_struct, raw_buffer, 4, pmatch, 0);
    if(status == REG_NOMATCH) {
        printf("[parse request] invalid header\n");
    } else {
        strncpy(method, raw_buffer + pmatch[1].rm_so, pmatch[1].rm_eo - pmatch[1].rm_so);
//        method[strlen(method)] = 0;
        method[pmatch[1].rm_eo - pmatch[1].rm_so] = 0;

        strncpy(path, raw_buffer + pmatch[2].rm_so, pmatch[2].rm_eo - pmatch[2].rm_so);
//        path[strlen(path)] = 0;
        path[pmatch[2].rm_eo - pmatch[2].rm_so] = 0;

        strncpy(protocal, raw_buffer + pmatch[3].rm_so, pmatch[3].rm_eo - pmatch[3].rm_so);
//        protocal[strlen(protocal)] = 0;
        protocal[pmatch[3].rm_eo - pmatch[3].rm_so] = 0;
    }


}