#include "connection_handler.h"
#include "logic.h"
#include "connection_handler.h"
#include <stdio.h>
#include "shared_context.h"
#include <unistd.h>

struct requests* initialize_global_context(void) {
    struct requests* req_context = malloc(sizeof(struct requests));
    initialize(req_context);
    return req_context;
}

int main(int argc, char *argv[]) {


    struct requests* req_context = initialize_global_context();
    // Initialize connection handler with shared resource
    initialize_handler_thread(req_context);

    // Begin server logic thread with shared resource
    initialize_logic_thread(req_context);

    // Listen for inturrupt, and send proper signals to other threads
    while(1) {
        /*printf("Server Still Alive\n");*/
        sleep(10);
    }
}
