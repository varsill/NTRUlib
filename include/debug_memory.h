#ifndef _debug_memory_h_
#define _debug_memory_h_

#include "memory.h"
#define malloc(X) debug_malloc(X)
#define free(X) debug_free(&X)

extern int elements_allocated;

#endif