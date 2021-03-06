#include "memory.h"
#include <stdio.h>
#include "hashtable.h"
int elements_allocated;
Hashtable * h;



unsigned long keyToInt(void* adr)
{
    return (unsigned long)adr;
}
void * debug_malloc(size_t size)
{
   
    void *p=malloc(size);
    elements_allocated++;
    printf("Memory at %d allocated. %d\n",(unsigned long)p, elements_allocated);
    if(insertElement(h, p, p)==false)printf("SOMETHING WRONG. \n");
    return p;
}

void debug_free(void** p)
{
    if(*p==NULL)return;
     int x = findElement(h, *p);
    if(removeElement(h, *p)==false)
    {
        printf("\033[0;31m"); //red ouput color
        printf("ATTEMPTED TO FREE UNALLOCATED MEMORY \n");
        printf("\033[0m");//default, white output color
    }
    else
    { 
        elements_allocated--;    
        printf("Memory at %d freed. %d index: %d\n", (unsigned long) *p,elements_allocated, x);
        free(*p);
   //     *p=NULL;
    }
    fflush(stdout);
    
    
}

void printMemoryStatus()
{
    printf("\n Memory status: %d unallocated memory chunks. \n", elements_allocated);
    fflush(stdout);
}



void printUnallocatedMemory()
{
    printf("\nUnallocated memory chunks:\n");
    for(int i=0; i<HASHTABLE_SIZE; i++)
    {
        if(h->elements_tab[i].is_empty!=true)
        printf("%d ", h->elements_tab[i].data);
    }
    printf("\n");
}