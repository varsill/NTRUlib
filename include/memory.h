#ifndef _memory_h_
#define _memory_h_
#include <stdlib.h>
extern elements_allocated;
void * debug_malloc(size_t);
void debug_free(void**);
void printMemoryStatus();
void pause(void);
#endif
