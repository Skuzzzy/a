#include "requests.h"
#include <string.h>

struct request* make_request(int type) {
    struct request* req = calloc(1, sizeof(struct request));
    req->request_type = type;
    return req;
}

struct request* make_say_request(char* message) {
    struct request* req = make_request(R_SAY);
    strncpy(req->data.say_req.message, message, MSGLEN_MAX);
    return req;
}

void dispose_request(struct request* request) {
    // Todo actually free requests in an appropriate manner
}
