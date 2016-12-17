#ifndef __NATGIOS_LOGIC__
#define __NATGIOS_LOGIC__

#include "shared_context.h"

void initialize_logic_thread(struct requests* request_context);
void* logic_loop(void* param);

#endif
