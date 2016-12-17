#include "connection_handler.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "shared_context.h"
#include "requests.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define INVALID_SOCK 0
#define client_len 32 // TODO FIXME
#define BUFFER_SIZE 1024

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

    int master_socket;

    if((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // TODO Verify this, should allow multiple connections at once
    int opt = 1;
    if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(master_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(master_socket, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    fd_set readfds;
    int clients[client_len] = {INVALID_SOCK};

    char buffer[BUFFER_SIZE];
    while(1) {
        FD_ZERO(&readfds);

        FD_SET(master_socket, &readfds);
        int max_fd = master_socket;
        for(int inx = 0; inx < client_len; inx++) {
            int sockfd = clients[inx];
            if(sockfd != INVALID_SOCK) {
                FD_SET(sockfd, &readfds);
                if(sockfd > max_fd) {
                    max_fd = sockfd;
                }
            }
        }

        int activity = select(max_fd+1, &readfds, NULL, NULL, NULL);
        if(activity < 0) {
            perror("select failed");
            exit(EXIT_FAILURE);
        }

        int addrlen = sizeof(address);
        if(FD_ISSET(master_socket, &readfds)) {
            int new_socket;
            if((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("accept failed");
                exit(EXIT_FAILURE);
            }
            printf("New connection %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
            for(int inx; inx < client_len; inx++) {
                // Todo expand client socket buffer if need be
                if(clients[inx] == INVALID_SOCK) {
                    printf("Placed client in %d\n", inx);
                    clients[inx] = new_socket;
                    break;
                }
            }
        }
        else {
            int inx = 0;
            while(activity > 0) {
                if(FD_ISSET(clients[inx], &readfds)) {
                    int sock_fd = clients[inx];
                    int amount_read;
                    if((amount_read = read(sock_fd, buffer, BUFFER_SIZE)) == 0) {
                        getpeername(sock_fd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                        printf("Client disconnect %s:%d\n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                        close(sock_fd);
                        clients[inx] = INVALID_SOCK;
                    }
                    else {
                        printf("Received %d bytes,\n", amount_read);
                        for(int j = 0; j < amount_read; j++) {
                            printf("%d ", buffer[j]);
                        }
                        printf("\n");
                    }
                    activity--;
                }
                inx++;
            }
        }
        /*printf("connection handler\n");*/
        lock(gcontext);
        if(!has_requests(gcontext)) {
            /*printf("no requests\n");*/
            /*put_request(gcontext, make_say_request(0, "one"));*/
            /*put_request(gcontext, make_say_request(0, "two"));*/
            /*put_request(gcontext, make_say_request(0, "three"));*/
            /*put_request(gcontext, make_create_entity_request(480));*/
        }
        unlock(gcontext);
        // SELECT on all available sockets
        // IF our main socket, accept the connection and add it to the connection list
        // IF any other socket, it is a standard socket, and use protocol
        // Parse and pass the request off to the logic thread, via the shared resource
    }
}
