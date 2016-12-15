#ifndef __NATGIOS_SHARED_CONTEXT__
#define __NATGIOS_SHARED_CONTEXT__

#include <pthread.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct requests {
    SLIST_HEAD(requestq, entry) head;
    pthread_mutex_t req_q_mutex;
};

struct entry {
    SLIST_ENTRY(entry) entries;
    char* data;
};

void aquire(struct requests* req) {
    pthread_mutex_lock(&req->req_q_mutex);
}

bool has_requests(struct requests* req) {
    return !(SLIST_EMPTY(&req->head));
}

void put_request(struct requests* reqs, char* data) {
    struct entry* req = malloc(sizeof(struct entry));
    req->data = strdup(data); // Assume that data is a string
    SLIST_INSERT_HEAD(&reqs->head, req, entries);
}

char* get_request(struct requests* reqs) {
    struct entry* req = SLIST_FIRST(&reqs->head);
    SLIST_REMOVE_HEAD(&reqs->head, entries);
    char * dat = req->data;
    free(req);
    return dat;
}

void release(struct requests* reqs) {
    pthread_mutex_unlock(&reqs->req_q_mutex);
}

#endif
