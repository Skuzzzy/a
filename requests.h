#ifndef __NATGIOS_REQUESTS__
#define __NATGIOS_REQUESTS__

#include <stdlib.h>

#define R_MOVE 0
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
struct move_request {
    int direction;
};

#define R_SAY 1
#define MSGLEN_MAX 1024
struct say_request {
    char message[MSGLEN_MAX]; // Messages have a max length
};

#define R_CREATE_ENTITY 2
struct create_entity_request {
    long user_id;
};


struct request {
    int request_type;
    int entity_id;

    union {
        struct move_request move_req;
        struct say_request say_req;
        struct create_entity_request mk_entity_req;
    } data;

};

struct request* make_request(int type, long entity);
struct request* make_say_request(long entity, char * message);
struct request* make_create_entity_request(long user_id);
void dispose_request(struct request* request);

#endif
