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


struct request {
    int request_type;

    union {
        struct move_request move_req;
        struct say_request say_req;
    } data;

};

struct request* make_request(int type);
struct request* make_say_request(char * message);
void dispose_request(struct request* request);

#endif
