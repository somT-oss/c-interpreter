// #include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

const int HASHTABLE_SIZE = 10;

typedef struct HashNode {
    char *key; 
    char *value;
    struct HashNode *next_node; // Handle collisions
} HashNode;

typedef struct HashTable {
    HashNode **buckets; // pointer to a pointer to a HashNode struct
} HashTable;


unsigned int hash_function(char *key) {
    unsigned int hash = 0;
    int i = 0;
    while (key[i] != '\0'){
        hash = hash * 100 + key[i];
        i ++;
    }
    i = 0;
    return hash % HASHTABLE_SIZE;
};

HashTable *create_hashtable() {
    HashTable *table = malloc(sizeof(HashTable));
    table->buckets = malloc(sizeof(HashNode*) * HASHTABLE_SIZE); // allocate memory for a DS (pointer to a HashNode) * HASHTABLE_SIZE
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

// ChatGPT Implementation
void insert(HashTable *table, char *key, char *value) {
    unsigned int index = hash_function(key); // compute the hash for the key of the key:value you want to store in the hashtable
    HashNode *existing_node = table->buckets[index];

    if (existing_node != NULL) {
        char *node_key = existing_node->key;
        if(strcmp(node_key, key) == 0) {
            printf("key %s already exists at index %d\n", key, index);
            return;
        }
    } else {
        HashNode *node = malloc(sizeof(HashNode)); // create a new node
        node->key = key; // assign the new node a key
        node->value = value; // assign the new node a value
        node->next_node = table->buckets[index]; // assign the new node's next_node value to the value of the table's node at that index
                                                        // by default this will be NULL, if it exists, create a linked list DS connecting the 
                                                        // existing value at that index with the newly computed hash of the new node.
        table->buckets[index] = node; // 
        }
}

// Implemented this without looking at GPT LFG🚀🚀
int search(HashTable *table, char *key) {
    unsigned int index = hash_function(key);
    HashNode *node = table->buckets[index];
    
    if (!node) {
        printf("key %s not found \n", key);
        return 1;
    } else {
        printf("found key at index %d\n", index);
        printf("{%s:%s} \n", node->key, node->value);
        return 0;
    }
}


// Implemented this without looking at GPT LFG🚀🚀
// This is dogshit and is full of errors
/* int delete(HashTable *table, char *key) {
    unsigned int index = hash_function(key);
    HashNode *node = table->buckets[index];

    if (!node) {
        printf("key %s not found \n", key);
        return 1;
    } else {
        node->key = NULL;
        node->value = NULL;
        node->next_node = NULL;
        printf("deleted data at index %d", index);
        return 0;
    }
}
*/

void delete(HashTable *table,char *key) {
    unsigned int index = hash_function(key);
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;
    
    /*
        This block handles traversing the linked list until we get to the node with the same key as the one we want to delete
    */
    while (node != NULL && strcmp(node->key, key) != 0) {
        prev = node; // update the previous node with the new node
        node = node->next_node; // update the node with the next node
    }
    
    /*
        If after the traversal we don't don't find the node, just return.
    */
    if (node == NULL) return; // Key not found
    
    /*
        We enter this block when we have found the key in our node with the same key we want to delete. 
        Two things can be observed here

        1. If the key is in the first node, update the [head node | current node | node at the ith index] with the value of linked next node in the linked list
        Linked List Dictionationary: {key1:value1} -> {key2:value2} -> {key3:value3}
        if the key == key1 and key1 is the first node in the linked list
 
        2. If the key is in the middle of the linked list, update the previous node.next value with the node.next value of the key the node is in.
        Linked List Dictionationary: {key1:value1} -> {key2:value2} -> {key3:value3}
        if the key == key2 and key2 is the first node in the linked list        
    */
    if (prev == NULL) {
        /*
            New linked list {key2:value2} -> {key3:value3}    
        */
        table->buckets[index] = node->next_node;
    } else {
        /*
            New linked list {key1:value1} -> {key3:value3} 
        */
        prev->next_node = node->next_node;
    }
    if (node->key != NULL && node->key != key) {
        // Free the dynamically allocated key
        free(node->key); 
    }
    
    // Free the node itself
    free(node);
}


void print_hashtable(HashTable *table) {
    for (int i = 0; i < HASHTABLE_SIZE; i ++) { // loop through the size of the hashtable
        HashNode *node = table->buckets[i];  // get the node at the ith position
        if (node == NULL) {
            printf("index: %d \n", i);
        } else {
            while (node != NULL) { // while the node is not null
                printf("index: %d -> {%s:%s}\n", i, node->key, node->value); // print the key of the node somto:23
                node = node->next_node; // set the node to node.next
            }
        }
    }
}


int main() {
    printf("This is my custom implementation of a hashtable\n");
    HashTable *my_hashtable = create_hashtable(); // create a hashtable
    insert(my_hashtable, "somto", "10"); // insert the values {"somto": "23"}
    insert(my_hashtable, "chibueze", "9"); // insert the values {"chibueze": "9"}
    insert(my_hashtable, "chibueze", "9"); // insert the values {"chibueze": "9"}
    delete(my_hashtable, "chibueze");
    print_hashtable(my_hashtable);
}