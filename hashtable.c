/*
Karl Toby Rosenberg
*/

#include "hashtable.h"

int main()
{
    //double load_factor = DEFAULTLOADFACTOR;

    printf("%s", "TEST\n");

    node_t** hash_table = (node_t**)calloc(100, sizeof(node_t*));

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

    return 0;
}

node_t* add_table_entry(char* key, uint64_t value, uint64_t table_size, node_t** table)
{


    return 0;
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