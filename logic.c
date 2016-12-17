#include "logic.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "shared_context.h"
#include <stdlib.h>

void initialize_logic_thread(struct requests* request_context) {
    pthread_t logic_thread;
    int res = pthread_create(&logic_thread, NULL,
            logic_loop, (void*)request_context);
    if(res != 0) {
        perror("Failed to initialize logic thread");
        exit(EXIT_FAILURE);
    }
}

void * logic_loop(void * param) {
    struct requests* gcontext = (struct requests*)param;

    while(1) {
        lock(gcontext);
        while(has_requests(gcontext)) {
            struct request * r = get_request(gcontext);
            if(r->request_type == R_SAY) {
                printf("%s\n", r->data.say_req.message);
            }
            else {
                printf("Unknown Request Type %d\n", r->request_type);
            }
            dispose_request(r);
        }
        /*printf("Logic Thread\n");*/
        unlock(gcontext);
    }
    return NULL;
}

