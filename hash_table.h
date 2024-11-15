#ifndef HASHTABLE_H
#define HASHTABLE_H

// #include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// #define HASHTABLE_SIZE 10;

typedef struct HashNode {
    char *key; 
    char *value;
    struct HashNode *next_node; // Handle collisions
} HashNode;

typedef struct HashTable {
    HashNode **buckets; // pointer to a pointer to a HashNode struct
} HashTable;


unsigned int hash_function(char *key);
HashTable *create_hashtable();
// modified ChatGPT Implementation
void insert(HashTable *table, char *key, char *value);
// Implemented this without looking at GPT LFG🚀🚀
int search(HashTable *table, char *key);
void delete_key(HashTable *table, char *key);
void print_hashtable(HashTable *table);
void delete_table(HashTable *table);

#endif