#ifndef __NATGIOS_CONNECTION_HANDLER__
#define __NATGIOS_CONNECTION_HANDLER__

void initialize_handler_thread(void);
void* handler_loop(void* param);

#endif
