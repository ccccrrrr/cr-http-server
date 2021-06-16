//
// Created by ccrr on 6/9/21.
//

#ifndef HTTP_SERVER_2_CONFIG_H
#define HTTP_SERVER_2_CONFIG_H

char Content_Type[][20] = {
        "text/html",
        "text/plain",
        "image/gif",
        "image/jpeg",
        "image/png",
        "text/markdown",
};


const char mount_path[50] = "/home/ccrr/http-server/root";

#define PORT 8081

#define MAX_EVENTS 10

#define GET_FAIL "GET FAILED! THERE IS NO SUCH FILE!"

#define POST_SUCCESS "FILE IS CREATED!"

#define PATH_NOT_FOUND "The PATH is INVALID!"

#define DELETE_SUCCESS "DELETE SUCCESSFULLY!"

#define DELETE_FAIL "DELETE FAILED!"

#define MAX_CONTENT_LENGTH 65535

#define POST_FAIL "FILE CREATION FAILED!"

#endif //HTTP_SERVER_2_CONFIG_H
