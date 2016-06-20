/*
Karl Toby Rosenberg
*/

#include "hashtable.h"

double load_factor_threshold = DEFAULTLOADFACTOR;
uint64_t table_size = 11;
uint64_t number_entries = 0;

int main()
{
    printf("%s", "TEST\n");

    node_t** hash_table = initialize_table(table_size);
    if(hash_table == NULL)
    {
        exit(-1);
    }

    /*

    add_front("hello", 1, &(hash_table[0]));

    print_chain(hash_table[0]);

    add_front("world", 2, &(hash_table[0]));
    add_front("!", 1, &(hash_table[1]));

    print_chain(hash_table[0]);
    print_chain(hash_table[1]);

    printf("%s", "WEEEEEEEE\n"); 
    print_table(100, hash_table);

    free(remove_front(&(hash_table[0])));
    free(remove_front(&(hash_table[0])));
    print_chain(hash_table[0]);
    free(remove_front(&(hash_table[1])));
    print_chain(hash_table[1]);

    */

    add_table_entry("Hello", 1, table_size, &hash_table);
    printf("\nnow in main: %s\n", "Added <Hello:1>?");

    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    add_table_entry("world", 2, table_size, &hash_table);
    printf("\nnow in main: %s\n", "Added <world:2>?");

    add_table_entry("Hello", 2, table_size, &hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    remove_table_entry("world", table_size, &hash_table);
    printf("\nnow in main: %s\n", "removed world?");
    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");


    return 0;
}

node_t** initialize_table(uint64_t table_size)
{
    node_t** table_allocate = (node_t**)calloc(table_size, sizeof(node_t*));
    return table_allocate; 
}

uint64_t hash(char* key)
{
    //variation of Jenkins one-at-a-time hash function
    uint32_t hash_val = 0;  
    char ch = 1;
    while((ch = *key++))
    {
        hash_val += ch;
        hash_val += (hash_val<<10);
        hash_val ^= (hash_val>>6);
    }
    
    hash_val += (hash_val<<3);
    hash_val ^= (hash_val>>11);
    hash_val += (hash_val<<15);

    return (uint64_t)hash_val;
}

//FINISH LATER, returns original table by default
int resize_table(uint64_t table_size, node_t*** table_ptr)
{
    //~TO-DO
    node_t** larger_table = initialize_table((table_size << 1));
    //return larger_table;
    return 0;
}

node_t* add_table_entry(char* key, uint64_t value, uint64_t table_size, node_t*** table_ptr)
{
    if(key == NULL || table_size <= 0 || table_ptr == NULL || *table_ptr == NULL)return NULL;

    //calculate index using hash function
    uint64_t hash_index = hash(key)%table_size;

    //check whether key already exists in linked-list chain (check key-value pairs)
    //if exists, update value (for example, increment a word frequency counter)
    //if does not exist
    node_t** chain_ptr = &((*table_ptr)[hash_index]);
    node_t* current = *chain_ptr;
    
    while( current && strcmp(key, ((current)->key)) != 0 )
    {
        current = current->next;
    }

    //entry does not exist
    if(current == NULL)
    {
        //check whether load factor threshold will be exceeded with the addition of the new item,
        //if so, resize table and rehash entries, rehash the new entry, then place it
        //otherwise just place the new entry at the front of the linked-list chain

        if( (double)((number_entries + 1)/table_size) > load_factor_threshold )
        {
            //~TO-DO, resize the table
            if((resize_table(table_size, table_ptr) != 0))return NULL;
        }

        node_t* new_entry = NULL;
        if((new_entry = add_front(key, value, chain_ptr)))
        {
            number_entries++;
            printf("\n%s", "In add_table_entry");
            printf("\n\n(*chain_ptr)->key %s\n", (*chain_ptr)->key);
            printf("%s\n", "calling print_chain in add_table_entry():");
            print_chain(*chain_ptr);
            printf("\n%s\n", "calling print_table in add_table_entry():");
            print_table(table_size, *table_ptr);
            printf("\n");
            return new_entry;
        }
        else
        {
            return NULL;
        }
    }
    //entry exists, update value
    else
    {
        current->value += value;
        return current;
    }
}

node_t* remove_table_entry(char* key, uint64_t table_size, node_t*** table_ptr)
{
    if(key == NULL || table_size <= 0 || table_ptr == NULL || *table_ptr == NULL)return NULL;

    //calculate index using hash function
    uint64_t hash_index = hash(key)%table_size;

    //check whether key already exists in linked-list chain (check key-value pairs)
    //if exists, update value (for example, increment a word frequency counter)
    //if does not exist
    
    node_t** current = &((*table_ptr)[hash_index]);
    
    while(*current && strcmp(key, ((*current)->key)) != 0)
    {
        current = &(*current)->next;
    }

    //entry does not exist
    if(!(*current))return NULL;
    
    node_t* to_remove = *current;
    *current = (to_remove)->next;
    to_remove->next = NULL;
    number_entries--;
    return to_remove;
}

int print_table(uint64_t table_size, node_t** table)
{
    if(!table)return -1;
    
    unsigned int i = 0;
    for(; i < table_size; ++i)
    {
        printf("%s %d\n", "chain index", i);
        printf("%s", "{ ");
        if(table[i])
        {
            print_chain(table[i]);
        }
        printf("%s\n", " }");
    }

    return 0;
}