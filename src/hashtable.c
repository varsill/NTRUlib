#include "hashtable.h"

Hashtable* createHashtable(unsigned long(*_keyToIntFunction)(void*))
{
    Hashtable * h = (Hashtable*)malloc(sizeof(Hashtable));
    for(int i=0; i<HASHTABLE_SIZE; i++)
    {
        h->elements_tab[i].is_empty=true;
        h->elements_tab[i].was_deleted=false;
        h->elements_tab[i].key=NULL;
    }
    h->keyToIntFunction=_keyToIntFunction;
    return h;

}

unsigned long hash(unsigned long key, int number_of_tries)
{
    return ((key%HASHTABLE_SIZE)+number_of_tries)%HASHTABLE_SIZE;
}


unsigned long getHash(const Hashtable * hashtable, void* key, int number_of_tries)
{
    unsigned long numerical_key=hashtable->keyToIntFunction(key);
    return hash(numerical_key, number_of_tries);
}



//Linear conficts resolving
bool insertElement(Hashtable* hashtable, void* key, void* data)
{
    int i=0;
    int h=-1;
    do{
        if(h>0&&hashtable->elements_tab[h].key==key)return false;//DATA WITH THAT KEY IS ALREADY IN TABLE
        h= getHash(hashtable, key, i);
        i++;
        
    }while(i<HASHTABLE_SIZE&&hashtable->elements_tab[h].is_empty!=true);
    if(i>HASHTABLE_SIZE)return false ;//not enough space in the hashtable
    hashtable->elements_tab[h].is_empty=false;
    hashtable->elements_tab[h].was_deleted=false;
    hashtable->elements_tab[h].data=data;
    hashtable->elements_tab[h].key=key;
    return true;

}

int findElement(Hashtable* hashtable, void* key)
{
    int i=0;
    int h;
    do{
        h= getHash(hashtable, key, i);
        i++;
    }while(i<HASHTABLE_SIZE&&hashtable->elements_tab[h].key!=key&&(hashtable->elements_tab[h].is_empty==false||hashtable->elements_tab[h].was_deleted==true));
    
    if(hashtable->elements_tab[h].key==key)return h;
    return -1;//not found
}
bool removeElement(Hashtable* hashtable, void* key)
{
    int h  = findElement(hashtable, key);
    if(h==-1)return false; //element with that key is not in the hashtable
    hashtable->elements_tab[h].is_empty=true;
    hashtable->elements_tab[h].was_deleted=true;
    hashtable->elements_tab[h].key=NULL;
    return true;
}

unsigned int countElements(Hashtable* hashtable)
{
    int x=0;
    for(int i=0; i<HASHTABLE_SIZE; i++)
    {
        if(hashtable->elements_tab[i].is_empty==false)x++;
    }
    return x;
}

void deleteHashtable(Hashtable* hashtable)
{
    free(hashtable);
}