#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets; //arreglo de pares
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long valorHash;
    
    valorHash = hash(key, map->capacity);
    if (map->buckets[valorHash] == NULL)
        {
            map->buckets[valorHash] = (Pair *) malloc (sizeof(Pair *));
            map->buckets[valorHash]->key = key;
            map->buckets[valorHash]->value = value;
            map->current = valorHash;
            map->size++;
        }
    else{
        while (map->buckets[valorHash] != NULL && map->buckets[valorHash]->key != NULL)
        {
            if (is_equal(key, map->buckets[valorHash]->key) == 1)
                return;
            valorHash = (1+valorHash) % map->capacity;     
        }
        if (map->buckets[valorHash] == NULL)
        {
            map->buckets[valorHash] = (Pair *) malloc (sizeof(Pair *));
            map->buckets[valorHash]->key = key;
            map->buckets[valorHash]->value = value;
            map->current = valorHash;
            map->size++;                
            return;
        }
        else{
            map->buckets[valorHash]->key = key;
            map->buckets[valorHash]->value = value;
        }
    }  
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap * new = (HashMap *) malloc (sizeof(HashMap));
    new->buckets = ((Pair **) calloc (capacity, sizeof(Pair *)));
    new->size = 0;
    new->current = -1;
    new->capacity = capacity;
    return new;
}


void eraseMap(HashMap * map,  char * key) {
    long valorHash;
    valorHash = hash(key, map->capacity);
    if (map->buckets[valorHash]->key == NULL){
        return;
    }
        
    if (is_equal(map->buckets[valorHash]->key, key) == 1){
        map->buckets[valorHash]->key = NULL;
        map->size--;
    }
    else{
        while (map->buckets[valorHash] != NULL && map->buckets[valorHash]->key != NULL)
        {
            if (is_equal(key, map->buckets[valorHash]->key) == 1)
            {
                map->buckets[valorHash]->key = NULL;
                map->size--;
                break;
            }
            if (map->buckets[valorHash]->key == NULL){
                return;
            }
            valorHash = (1+valorHash) % map->capacity;     
        }
    } 
}

Pair * searchMap(HashMap * map,  char * key) {   
    long valorHash;

    valorHash = hash(key, map->capacity);

    if (is_equal(map->buckets[valorHash]->key, key) == 1)
        {
            map->current = valorHash;
            return map->buckets[valorHash];
        }
    else{
        while (map->buckets[valorHash] != NULL && map->buckets[valorHash]->key != NULL)
        {
            if (is_equal(key, map->buckets[valorHash]->key) == 1)
            {
                map->current = valorHash;
                return map->buckets[valorHash];
                break;
            }
            valorHash = (1+valorHash) % map->capacity;     
        }
        return NULL;
    }  

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
