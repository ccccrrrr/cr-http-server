#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseRequest.c"
#include "method.c"
#include "read.c"
#include "parse_response.c"
#include "header.h"


int generate_response(const char * raw_request, char * recv_buffer) {

    struct Request request;
    memset(&request, 0, sizeof(struct Request));
//    parseRequest((const char *)raw_request, &request);
//  regex method
    parse_request2((const char *)raw_request, &request);

    struct Response response;
    response.file = (struct file_reader *)malloc(sizeof(struct file_reader));
    memset(response.file, 0, sizeof(struct file_reader));

    char content[MAX_CONTENT_LENGTH] = {0};
    memset(content, 0, sizeof(content));
    memset(recv_buffer, 0, sizeof(*recv_buffer));

    switch(request.method) {
        case METHOD_GET:
            method_get(&request, &response);
            convert_get_response_to_buffer(&response, recv_buffer);
            break;
        case METHOD_POST:
            read_content(content, raw_request);
            method_post(&request, &response, content);
            convert_post_response_to_buffer(&response, recv_buffer);
            break;
        case METHOD_DELETE:
            method_delete(&request, &response);
            convert_delete_response_to_buffer(&response, recv_buffer);
            break;
        case METHOD_UNDEFINED:
            printf("undefined method.\n");
            method_undefined(&request, &response);
            break;
        default:
            break;
    }
    return request.is_keep_alive;
}