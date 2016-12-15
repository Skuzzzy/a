#include "connection_handler.h"
#include "logic.h"
#include "connection_handler.h"
#include <stdio.h>




int main(int argc, char *argv[]) {


    // Initialize connection handler with shared resource
    initialize_handler_thread();

    // Begin server logic thread with shared resource
    initialize_logic_thread();

    // Listen for inturrupt, and send proper signals to other threads
    while(1) {
        printf("Waiting for something to happen");
    }
}
