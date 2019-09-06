#ifndef _hashtable_h_
#define _hashtable_h_
#define HASHTABLE_SIZE 10000
#include <stdbool.h>
#include <stdlib.h>

typedef struct 
{
    void* data;
    void* key;
    bool is_empty;
    bool was_deleted;
} Element;


typedef struct 
{
    Element elements_tab[HASHTABLE_SIZE];
    unsigned long(*keyToIntFunction)(void*);
} Hashtable;

void deleteHashtable(Hashtable* hashtable);
unsigned int countElements(Hashtable* hashtable);
bool removeElement(Hashtable* hashtable, void* key);
int findElement(Hashtable* hashtable, void* key);
bool insertElement(Hashtable* hashtable, void* key, void* data);
unsigned long getHash(const Hashtable * hashtable, void* key, int number_of_tries);
unsigned long hash(unsigned long key, int number_of_tries);
Hashtable* createHashtable(unsigned long(*_keyToIntFunction)(void*));


#endif