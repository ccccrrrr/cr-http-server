//
// Created by ccrr on 6/16/21.
//

#ifndef HTTP_SERVER_2_PARSEREQUEST_H
#define HTTP_SERVER_2_PARSEREQUEST_H
#include "header.h"
void parse_request2(const char *raw_request, struct Request * req);
void parseRequest(const char * raw_request, struct Request * req);
#endif //HTTP_SERVER_2_PARSEREQUEST_H
