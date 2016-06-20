/*
Karl Toby Rosenberg
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#ifndef HASHCHAIN_H
#include "hashchain.h"
#endif

#define DEFAULTSIZE 97
#define DEFAULTLOADFACTOR 0.75

/*NOTE: I will use this struct rather than the various variables scattered around,
but I would like to finish this version of the program first.
typedef struct hash_table
{
    node_t** table;
    uint64_t number_entries;
    uint64_t table_size;
    double load_factor_threshold;
}hash_table_t;
*/

node_t** initialize_table(uint64_t table_size);
uint64_t hash(char* key);
int resize_table(uint64_t table_size, node_t*** table_ptr); 
node_t* put_entry(char* key, uint64_t value, uint64_t table_size, node_t*** table_ptr);
int64_t get(char* key, uint64_t table_size, node_t** table);
node_t* remove_entry(char* key, uint64_t table_size, node_t*** table_ptr);
int clear_table(uint64_t table_size, node_t** table);
int print_table(uint64_t table_size, node_t** table);

#endif