#ifndef _memory_h_
#define _memory_h_

#include <stdlib.h>
#include "hashtable.h"
extern int elements_allocated;
extern Hashtable * h;
extern unsigned long keyToInt(void* adr);
void * debug_malloc(size_t);
void debug_free(void**);
void printMemoryStatus();
void printUnallocatedMemory();
#endif
