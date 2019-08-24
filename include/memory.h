#ifndef _memory_h_
#define _memory_h_
#include <stdlib.h>

void * debug_malloc(size_t);
void debug_free(void**);
void printMemoryStatus();
#endif
