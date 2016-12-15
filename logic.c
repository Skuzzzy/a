#include "logic.h"
#include <pthread.h>
#include <stdio.h>

void initialize_logic_thread(void) {
    pthread_t logic_thread;
    int res = pthread_create(&logic_thread, NULL, logic_loop, (void*)NULL);
}

void * logic_loop(void * param) {
    while(1) {
        printf("Logic Thread\n");
    }
    return NULL;
}

