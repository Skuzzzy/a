#ifndef __NATGIOS_SHARED_CONTEXT__
#define __NATGIOS_SHARED_CONTEXT__

#include <pthread.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// TODO BREAK OUT REQUEST INTO ITS OWN FILE
struct request {

};

struct requests {
    SLIST_HEAD(requestq, entry) head;
    pthread_mutex_t req_q_mutex;
};

struct entry {
    SLIST_ENTRY(entry) entries;
    char* data;
};


void initialize(struct requests* reqs);

void lock(struct requests* reqs);

void unlock(struct requests* reqs);

bool has_requests(struct requests* req);

void put_request(struct requests* reqs, char* data);

char* get_request(struct requests* reqs);

#endif
