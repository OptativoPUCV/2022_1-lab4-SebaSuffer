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
    long valorHash, i;
    
    valorHash = hash(key, map->capacity);
    if (is_equal(key, map->buckets[valorHash]->key)== 0 || map->buckets[valorHash]->key == NULL || map->buckets[valorHash]->value == NULL)
        {
            map->buckets[valorHash]->key = key;
            map->buckets[valorHash]->value = value;
            map->current = valorHash;
            map->capacity++;
        }
    else{
        for (i = valorHash; i < map->capacity; i++)
        {
            if (is_equal(key, map->buckets[i]->key)== 0 || map->buckets[i]->key == NULL || map->buckets[i]->value == NULL)
            {
                map->buckets = (Pair **) malloc (sizeof(Pair *));
                map->buckets[i]->key = key;
                map->buckets[i]->value = value;
                map->current = valorHash;
                map->capacity++;
            }
            else{
                valorHash = hash(key, map->capacity)+1;
            }
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


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
