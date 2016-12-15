#include "connection_handler.h"
#include "logic.h"
#include "connection_handler.h"
#include <stdio.h>
#include "shared_context.h"
#include <unistd.h>

void initialize_global_context(void) {
    initialize(&gcontext);
}

int main(int argc, char *argv[]) {


    initialize_global_context();
    // Initialize connection handler with shared resource
    initialize_handler_thread();

    // Begin server logic thread with shared resource
    initialize_logic_thread();

    // Listen for inturrupt, and send proper signals to other threads
    while(1) {
        sleep(10);
        printf("Server Still Alive");
    }
}
