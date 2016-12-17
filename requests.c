#include "requests.h"
#include <string.h>

struct request* make_request(int type, long entity) {
    struct request* req = calloc(1, sizeof(struct request));
    req->request_type = type;
    req->entity_id = entity;
    return req;
}

struct request* make_say_request(long entity, char* message) {
    struct request* req = make_request(R_SAY, entity);
    strncpy(req->data.say_req.message, message, MSGLEN_MAX);
    return req;
}

void dispose_request(struct request* request) {
    // Todo actually free requests in an appropriate manner
    free(request);
    // As of right now, no requests make any allocations,
    // but perhaps in the future
}

struct request* make_create_entity_request(long user_id) {
    struct request* req = make_request(R_CREATE_ENTITY, -1);
    req->data.mk_entity_req.user_id = user_id;
    return req;
}
