#include "memory.h"
#include <stdio.h>
int elements_allocated;

void * debug_malloc(size_t size)
{
    
    void *p=malloc(size);
    elements_allocated++;
    printf("Memory allocated. %d\n", elements_allocated);
    return p;
}

void debug_free(void** p)
{
    if(*p==NULL)return;
    free(*p);
    elements_allocated--;
    *p=NULL;
    printf("Memory free. %d\n", elements_allocated);
}

void printMemoryStatus()
{
    printf("\n Memory status: %d unallocated memory chunks. \n", elements_allocated);
    fflush(stdout);
}

void pause ( void ) 
{ 
  printf ( "Press [Enter] to continue . . ." );
  fflush ( stdout );
  getchar();
} 