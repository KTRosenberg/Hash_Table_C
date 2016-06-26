/*
Karl Toby Rosenberg

hashtable:
    header for an implementation of a hash table with separate chaining
    and automatic resizing, allows the user to specify a custom hash function
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>

#define DEFAULTSIZE 11
#define DEFAULTMAXLOAD 0.75
#define DEFAULTHASH &hash_default
#define DEFAULTHASH2 &hash_default_2

#define NEEDTORESIZE \
(((hash_table->table_size << 1) + 1 > (hash_table->table_size)) && \
(double)(hash_table->num_records + 1)/(double)((hash_table->table_size)) > \
hash_table->max_load)


#ifndef HASHCHAIN_H
#include "hashchain.h"
#endif


typedef struct hash_table
{
    size_t     table_size;
    size_t     num_records;
    double     max_load;
    uint64_t   (*hash_function)(char*);
    record_t** lists;
}hash_table_t;

hash_table_t* init_hash_table(size_t table_size, double load_threshold, uint64_t (*hash_function)(char*));
uint64_t hash_default(char* key);
uint64_t hash_default_2(char* key);
int resize_table(hash_table_t* hash_table); 
record_t* put_record(char* key, uint64_t value, hash_table_t* hash_table);
int64_t get_value(char* key, hash_table_t* hash_table);
record_t* remove_record(char* key, hash_table_t* hash_table);
int print_table(hash_table_t* hash_table);
void clear_table(hash_table_t* hash_table);
void del_hash_table(hash_table_t** hash_table);

#endif
