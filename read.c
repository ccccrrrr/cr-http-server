//
// Created by ccrr on 6/16/21.
//

void read_body(char * content, const char * raw_request, int start_point) {
    int ptr = 0;
    while(raw_request[start_point] > 0) {
        while(raw_request[start_point] != '\n' && raw_request[start_point] > 0)
            content[ptr++] = raw_request[start_point++];
        if(raw_request[start_point] == '\n')
            content[ptr++] = raw_request[start_point++];
        else
            break;
    }
    content[ptr] = 0;
}

void read_content(char * content, const char * raw_request) {
    int ptr2 = 0;
    while(1) {
        if (raw_request[ptr2] == '\r' && raw_request[ptr2 + 1] == '\n' && raw_request[ptr2 + 2] == '\r' && raw_request[ptr2 + 3] == '\n')
            break;
        ptr2++;
    }
    ptr2 += 4;
    read_body(content, raw_request, ptr2);
}
