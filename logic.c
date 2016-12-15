#include "logic.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "shared_context.h"
#include <stdlib.h>

void initialize_logic_thread(void) {
    pthread_t logic_thread;
    int res = pthread_create(&logic_thread, NULL, logic_loop, (void*)NULL);
    if(res != 0) {
        perror("Failed to initialize logic thread");
        exit(EXIT_FAILURE);
    }
}

void * logic_loop(void * param) {
    while(1) {
        lock(&gcontext);
        while(has_requests(&gcontext)) {
            char * r = get_request(&gcontext);
            printf("%s\n", r);
            free(r);
        }
        /*printf("Logic Thread\n");*/
        unlock(&gcontext);
    }
    return NULL;
}

