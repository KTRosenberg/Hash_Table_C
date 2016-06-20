/*
Karl Toby Rosenberg
*/

#ifndef HASHCHAIN_H
#define HASHCHAIN_H

#ifndef HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#endif

typedef struct node
{
    uint64_t value;
    struct node* next;
    char* key;
}node_t;

node_t* add_front(char* key, uint64_t value, node_t** head);
node_t* remove_front(node_t** head);

//add a remove_by_ptr function

void free_chain(node_t** head);
void print_chain(node_t* head);

#endif