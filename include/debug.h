#ifndef _debug_memory_h_
#define _debug_memory_h_
#include <stdio.h>

void pause(void);
#define printDebug(msg) printf(msg);fflush(stdout);

#ifdef DEBUG_MEMORY
    #include "memory.h"
    #define malloc(X) debug_malloc(X)
    #define free(X) debug_free(&X)
    #define START_DEBUG h=createHashtable(keyToInt);
    #define STOP_DEBUG deleteHashtable(h);
#endif
#ifndef DEBUG_MEMORY
    #define START_DEBUG 
    #define STOP_DEBUG
#endif
#endif