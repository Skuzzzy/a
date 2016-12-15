
all:
	gcc -g -pthread server.c logic.c connection_handler.c shared_context.c
