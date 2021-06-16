//
// Created by ccrr on 6/16/21.
//

#ifndef HTTP_SERVER_2_REGEX_H
#define HTTP_SERVER_2_REGEX_H

const char reg_method_path_protocal_pattern[30] = "^(\\w+) (.+) (.+)\r\n";
const char reg_connection_pattern[30] =  "Connection: (.+)\r\n";
const char reg_content_length[30] = "Content-Length: (.+)\r\n";
const char reg_content_type[30] = "Content-Type: (.+)\r\n";

int IF_KEEP_ALIVE = 0x0;

void parse_header(const char * raw_buffer, int buffer_length, int * if_keep_alive, int * content_length, char * content_type, char * method, char * path, char * protocal);
void init_regex();

#endif //HTTP_SERVER_2_REGEX_H
