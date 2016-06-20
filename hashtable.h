/*
Karl Toby Rosenberg
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "hashchain.h"

#define DEFAULTSIZE 97
#define DEFAULTLOADFACTOR 0.75

node_t** initialize_table(uint64_t table_size);
uint64_t hash(char* key);
int resize_table(uint64_t table_size, node_t*** table_ptr); 
node_t* add_table_entry(char* key, uint64_t value, uint64_t table_size, node_t*** table_ptr);
node_t* remove_table_entry(char* key, uint64_t table_size, node_t*** table_ptr);
int clear_table(uint64_t table_size, node_t** table);
int print_table(uint64_t table_size, node_t** table);

#endif