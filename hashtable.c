/*
Karl Toby Rosenberg
*/

#include "hashtable.h"

double load_factor_threshold = DEFAULTLOADFACTOR;
uint64_t table_size = 11; //I should switch to size_t
uint64_t number_entries = 0;

int main()
{

    node_t** hash_table = initialize_table(table_size);
    if(!hash_table)
    {
        exit(-1);
    }

    load_factor_threshold = 0.2; //test value so fewer entries necessary to qualify for resizing

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

    put_entry("Hello", 1, table_size, &hash_table);
    printf("\nnow in main: %s\n", "Added <Hello:1>?");

    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    put_entry("world", 2, table_size, &hash_table);
    printf("\nnow in main: %s\n", "Added <world:2>?");

    put_entry("Hello", 2, table_size, &hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    remove_entry("world", table_size, &hash_table);
    printf("\nnow in main: %s\n", "removed world?");

    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");
    
    put_entry("Yay", 4, table_size, &hash_table);
    printf("\nnow in main: %s\n", "Added <Yay:4>?");

    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    put_entry("Hoorah", 5, table_size, &hash_table);
    printf("\nnow in main: %s\n", "Added <Hoorah:5>?");

    print_table(table_size, hash_table);
    printf("\nnow in main: %s\n", "printed table in main?");

    printf("Number of entries: %lu table_size: %lu\n\n", (long unsigned)number_entries, (long unsigned)table_size);
    
    unsigned long i = 0;
    for(; i < table_size; ++i)
    {
        free_chain(&(hash_table[i]));
    }

    printf("\n%s\n", "print before final free, should have empty buckets:");
    print_table(table_size, hash_table);
    free(hash_table);

    hash_table = NULL;
    
    return 0;
}

node_t** initialize_table(uint64_t size)
{
    node_t** table_allocate = (node_t**)calloc(size, sizeof(node_t*));
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

//BUGGY CODE, POINTER ARITHMETIC MESSINESS
int resize_table(uint64_t size, node_t*** table_ptr)
{

    //What I am trying to do:
    //allocate memory for a table twice the size of the original
    if(!table_ptr || !(*table_ptr))return -1;

    uint64_t new_size = (size << 1);
    node_t** larger_table = initialize_table(new_size);

    node_t* to_transfer = NULL;
    uint64_t hash_index = 0; 
    uint64_t i = 0;

    printf("\n%s\n", "Inside resize_table");

    for(; i < size; ++i)
    {
        while(((*table_ptr)[i]))
        {
            if(!(to_transfer = remove_front( &((*table_ptr)[i]))) )return -1;
            hash_index = hash(to_transfer->key)%size;
            to_transfer->next = larger_table[hash_index];
            larger_table[hash_index] = to_transfer;
        }
    }
        //TESTING:
        ///////////////////////////////////////////
 
        printf("\n%s\n", "Inside resize_table after loop");

    
        printf("\n%s\n", "Try to print old table");
        print_table(table_size, *table_ptr);
        ///////////////////////////////////////////
    
    free(*table_ptr);
    //free(*table_ptr); //corrupts. So it was freed, but as I learned, freeing does not make a pointer NULL.
                                    //I have to set the pointer to NULL if I want the additional guard.

        ///////////////////////////////////////////
    
    table_size = new_size;
    (*table_ptr) = larger_table;

        ///////////////////////////////////////////

        printf("\n%s\n", "Try to print larger table");

        print_table(table_size, larger_table);

        printf("\ntable_size in resize_table() %lu\n", (unsigned long)table_size);
        ////////////////////////////////////////////

    return 0;
}

node_t* put_entry(char* key, uint64_t value, uint64_t size, node_t*** table_ptr)
{
    if(!key || size <= 0 || !table_ptr || !(*table_ptr))return NULL;

    //calculate index using hash function
    uint64_t hash_index = hash(key)%size;

    //check whether key already exists in linked-list chain (check key-value pairs)
    //if exists, update value (for example, increment a word frequency counter)
    //if does not exist
    node_t** chain_ptr = &((*table_ptr)[hash_index]);
    node_t* current = *chain_ptr;
    
    while(current && strcmp(key, ((current)->key)) != 0)
    {
        current = current->next;
    }

    //if entry does not exist
    if(!current)
    {
        //check whether load factor threshold will be exceeded with the addition of the new item,
        //if so, resize table and rehash entries, rehash the new entry, then place it
        //otherwise just place the new entry at the front of the linked-list chain

        printf("num_entries: %lu table_size: %lu load_factor_threshold: %f load_factor: %f\n\n", (long unsigned)number_entries, (long unsigned)table_size, load_factor_threshold, (double)((number_entries + 1)/(double)table_size));  
        if((double)((number_entries + 1)/(double)size) > load_factor_threshold )
        {
            printf("\n%s\n", "Try to resize...enter resize_table???");
            //~TO-DO, resize the table
            if((resize_table(size, table_ptr) != 0))return NULL;

            size = table_size;
            hash_index = hash(key)%size;
            chain_ptr = &((*table_ptr)[hash_index]);
            
            printf("\n%s\n", "Print the new table...after resize_table???");

            print_table(size, *table_ptr);
            
        }

        node_t* new_entry = NULL;
        if((new_entry = add_front(key, value, chain_ptr)))
        {
            number_entries++;
            /*
            printf("\n%s", "In add_table_entry");
            printf("\n\n(*chain_ptr)->key %s\n", (*chain_ptr)->key);
            printf("%s\n", "calling print_chain in add_table_entry():");
            print_chain(*chain_ptr);
            printf("\n%s\n", "calling print_table in add_table_entry():");
            print_table(table_size, *table_ptr);
            printf("\n");
            */
            return new_entry;
        }
        else
        {
            return NULL;
        }
    }
    //if entry exists, update its value
    else
    {
        current->value += value;
        return current;
    }
}

/*
    get

    if the key exists, returns the non-negative value mapped to the given key,
    otherwise returns -1
*/
int64_t get(char* key, uint64_t size, node_t** table)
{
    if(!key || size <= 0 || !table)return -1;

    //calculate index using hash function
    uint64_t hash_index = hash(key)%size;

    //if key exists in table, return its value, otherwise return 0;
    node_t* current = table[hash_index];
    
    while(current && strcmp(key, ((current)->key)) != 0)
    {
        current = current->next;
    }

    //if entry does not exist
    if(!current)return -1;

    //if entry exists
    return current->value;
}

node_t* remove_entry(char* key, uint64_t size, node_t*** table_ptr)
{
    if(!key || size <= 0 || !table_ptr || !(*table_ptr))return NULL;

    //calculate index using hash function
    uint64_t hash_index = hash(key)%size;

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
    to_remove->key = NULL;
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