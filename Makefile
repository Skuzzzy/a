
all:
	gcc -pthread server.c logic.c connection_handler.c
