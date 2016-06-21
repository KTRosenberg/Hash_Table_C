/*
Karl Toby Rosenberg
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
#define NEEDTORESIZE ((hash_table->table_size) << 1) != ULLONG_MAX && (double)(hash_table->num_records + 1)/(double)((hash_table->table_size)) > hash_table->max_load


#ifndef HASHCHAIN_H
#include "hashchain.h"
#endif


typedef struct hash_table
{
    record_t** lists;
    size_t     table_size;
    size_t     num_records;
    double     max_load;
}hash_table_t;

hash_table_t* init_hash_table(size_t table_size, double load_threshold);
uint64_t hash(char* key);
int resize_table(hash_table_t* hash_table); 
record_t* put_record(char* key, uint64_t value, hash_table_t* hash_table);
int64_t get_value(char* key, hash_table_t* hash_table);
record_t* remove_record(char* key, hash_table_t* hash_table);
int print_table(hash_table_t* hash_table);
void clear_table(hash_table_t* hash_table);
void del_hash_table(hash_table_t* hash_table);

#endif