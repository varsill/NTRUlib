#ifndef _debug_memory_h_
#define _debug_memory_h_
#include "config.h"
#ifdef DEBUG_MEMORY
#include "memory.h"
#define malloc(X) debug_malloc(X)
#define free(X) debug_free(&X)
#define START_DEBUG h=createHashtable(keyToInt);
#define STOP_DEBUG deleteHashtable(h);
#endif
#endif