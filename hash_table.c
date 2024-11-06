#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

const int HASHTABLE_SIZE = 10;

typedef struct HashNode {
    char *key; 
    char *value;
    struct HashNode *next_node; 
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

// My implementation
/* void insert(HashTable *table, char *key, char *value){
    unsigned int computed_hash = hash_function(key);
    HashNode key_value = {
        key = key,
        value=value
    };
    table->buckets = key_value; 
} 
*/

// ChatGPT Implementation
void insert(HashTable *table, char *key, char *value) {
    unsigned int computed_hash = hash_function(key); // compute the hash for the key of the key:value you want to store in the hashtable
    HashNode *node = malloc(sizeof(HashNode)); // create a new node
    node->key = key; // assign the new node a key
    node->value = value; // assign the new node a value
    node->next_node = table->buckets[computed_hash]; // assign the new node's next_node value to the value of the table's node at that index
                                                     // by default this will be NULL, if it exists, create a linked list DS connecting the 
                                                     // existing value at that index with the newly computed hash of the new node.
    table->buckets[computed_hash] = node; // 
}

int main() {
    printf("This is my custom implementation of a hashtable\n");
    HashTable *my_hashtable = create_hashtable(); // create a hashtable
    insert(my_hashtable, "somto", "10"); // insert the values {"somto": "23"}
    insert(my_hashtable, "chibueze", "9"); // insert the values {"chibueze": "25"}
    for (int i = 0; i < HASHTABLE_SIZE; i ++) { // loop through the size of the hashtable
        HashNode *node = my_hashtable->buckets[i];  // get the node at the ith position
        if (node == NULL) {
            printf("index: %d \n", i);
        } else {
            while (node != NULL) { // while the node is not null
            printf("index: %d -> {%s:%s}\n", i, node->key, node->value); // print the key of the node somto:23
            node = node->next_node; // set the node to node.next
        }
            // printf("index %d ", i);
            // printf("{'%s:%s}\n", node->key, node->value);
        }
        
    }


    // printf("%d\n", hash_function("somto"));
    // printf("%d\n", hash_function("david"));
    // printf("%d\n", hash_function("uchegbu"));
}