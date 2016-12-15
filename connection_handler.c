#include "connection_handler.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "shared_context.h"

void initialize_handler_thread(void) {
    // Grab a TCP port and prepare to accept connections on it.
    pthread_t handler_thread;
    int res = pthread_create(&handler_thread, NULL, handler_loop, (void*)NULL);
    if(res != 0) {
        perror("Failed to initialize connection handler");
        exit(EXIT_FAILURE);
    }
}

void* handler_loop(void* param) {
    while(1) {
        /*printf("connection handler\n");*/
        lock(&gcontext);
        if(!has_requests(&gcontext)) {
            /*printf("no requests\n");*/
            put_request(&gcontext, "one");
            put_request(&gcontext, "two");
            put_request(&gcontext, "three");
        }
        unlock(&gcontext);
        // SELECT on all available sockets
        // IF our main socket, accept the connection and add it to the connection list
        // IF any other socket, it is a standard socket, and use protocol
        // Parse and pass the request off to the logic thread, via the shared resource 
    }
}
