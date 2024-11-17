// #include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hash_table.h"

const int HASHTABLE_SIZE = 10;

unsigned int hash_function(char *key) {
    unsigned int hash = 0;
    int i = 0;
    unsigned int prime = 31;
    while (key[i] != '\0'){
        hash = (hash * prime) + key[i];
        i ++;
    }
    i = 0;
    return hash % HASHTABLE_SIZE;
};

HashTable *create_hashtable() {
    HashTable *table = malloc(sizeof(HashTable));
    if (!table) {
        printf("Failed to allocate memory");
        exit(1);
    }
    table->buckets = malloc(sizeof(HashNode*) * HASHTABLE_SIZE);
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// modified ChatGPT Implementation
void insert(HashTable *table, char *key, char *value) {
    unsigned int index = hash_function(key); // compute the hash for the key of the key:value you want to store in the hashtable
    HashNode *existing_node = table->buckets[index];

    if (existing_node != NULL) {
        char *node_key = existing_node->key;
        if(strcmp(node_key, key) == 0) {
            printf("key %s already exists at index %d\n", key, index); // checks if a key exists and does not allow addition of that same key
            return;
        }
    } else {
        HashNode *node = malloc(sizeof(HashNode)); 
        node->key = key; 
        node->value = value;
        node->next_node = table->buckets[index];
        table->buckets[index] = node; // 
        }
}

// Implemented this without looking at GPT LFG🚀🚀
int search(HashTable *table, char *key) {
    unsigned int index = hash_function(key);
    // printf("hash of %d is ", index);
    HashNode *node = table->buckets[index];
    
    if (node != NULL) {
        if(strcmp(node->key, key) != 0) {
            return 1;
        } 
        return 0;
        
    } else {
        return 1;
    }
}


char *get_key(HashTable *table, char *key) {
    if (!table) {
        printf("Invalid table");
        return NULL;
    } 
    unsigned int hash = hash_function(key);
    HashNode *node = table->buckets[hash];

    if (!node) {
        printf("NULL node");
        return NULL;
    } 
    return node->key;
}

void delete(HashTable *table,char *key) {
    unsigned int index = hash_function(key);
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;
    
    while (node != NULL && strcmp(node->key, key) != 0) {
        prev = node; // update the previous node with the new node
        node = node->next_node; // update the node with the next node
    }
    if (node == NULL) {
        return;
    } 
    if (prev == NULL) {
        table->buckets[index] = node->next_node;
    } else {
        prev->next_node = node->next_node;
    }
    if (node->key != NULL && node->key != key) {
        free(node->key); 
    }
    free(node);
}

// Implemented this without looking at GPT LFG🚀🚀
void delete_table(HashTable *table) { 
    for (int index = 0; index < HASHTABLE_SIZE; index ++) {
        HashNode *node = table->buckets[index];
        while (node != NULL) {
            HashNode *temp = node;
            node = node->next_node;
            // free(temp->key);
            free(temp);
        }    
    }
    free(table->buckets);
    free(table);
    printf("Deleted hashtable\n");
}


void print_hashtable(HashTable *table) {
    for (int i = 0; i < HASHTABLE_SIZE; i ++) { 
        HashNode *node = table->buckets[i]; 
        if (node == NULL) {
            printf("index: %d \n", i);
        } else {
            while (node != NULL) {
                printf("index: %d -> {%s:%s}\n", i, node->key, node->value);
                node = node->next_node;
            }
        }
    }
}