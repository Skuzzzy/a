#include "connection_handler.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "shared_context.h"
#include "requests.h"

void initialize_handler_thread(struct requests* request_context) {
    // Grab a TCP port and prepare to accept connections on it.
    pthread_t handler_thread;
    int res = pthread_create(&handler_thread, NULL,
                             handler_loop, (void*)request_context);
    if(res != 0) {
        perror("Failed to initialize connection handler");
        exit(EXIT_FAILURE);
    }
}

void* handler_loop(void* param) {
    struct requests* gcontext = (struct requests*) param;


    while(1) {
        /*printf("connection handler\n");*/
        lock(gcontext);
        if(!has_requests(gcontext)) {
            /*printf("no requests\n");*/
            put_request(gcontext, make_say_request("one"));
            put_request(gcontext, make_say_request("two"));
            put_request(gcontext, make_say_request("three"));
        }
        unlock(gcontext);
        // SELECT on all available sockets
        // IF our main socket, accept the connection and add it to the connection list
        // IF any other socket, it is a standard socket, and use protocol
        // Parse and pass the request off to the logic thread, via the shared resource 
    }
}
