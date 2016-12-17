
all:
	gcc -g -Wall -pthread server.c logic.c connection_handler.c shared_context.c requests.c
