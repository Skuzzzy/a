#ifndef __NATGIOS_CONNECTION_HANDLER__
#define __NATGIOS_CONNECTION_HANDLER__

#include "shared_context.h"

#define PORT 55000

void initialize_handler_thread(struct requests* request_context);
void* handler_loop(void* param);

#endif
