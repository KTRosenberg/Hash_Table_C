/*
Karl Toby Rosenberg
*/

#include "hashtable.h"

double load_factor_threshold = DEFAULTLOADFACTOR;
uint64_t table_size = 10;
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

    node_t* x = add_table_entry("Hello", 1, table_size, hash_table);
    free(x);
    print_table(table_size, hash_table);
    printf("%s\n", "I just called print_table after freeing the Hello entry, but the hello entry apparently still exists. Something is clearly not being linked correctly.");
    free(hash_table);


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
node_t** resize_table(uint64_t table_size, node_t** table)
{
    //~TO-DO
    node_t** larger_table = initialize_table((table_size << 1));
    //return larger_table;
    return table;
}

node_t* add_table_entry(char* key, uint64_t value, uint64_t table_size, node_t** table)
{
    if(key == NULL || table_size <= 0 || table == NULL)return NULL;

    //calculate index using hash function
    uint64_t hash_index = hash(key)%table_size;

    //check whether key already exists in linked-list chain (check key-value pairs)
    //if exists, update value (for example, increment a word frequency counter)
    //if does not exist
    node_t* chain_head = table[hash_index];
    node_t* current = chain_head;
    
    while(current && strcmp(key, ((current)->key)) != 0)
    {
        current = current->next;
    }

    if(current == NULL)
    {
        //check whether load factor threshold will be exceeded with the addition of the new item,
        //if so, resize table and rehash entries, rehash the new entry, then place it
        //otherwise just place the new entry at the front of the linked-list chain

        if( ((double)(number_entries + 1)/table_size) > load_factor_threshold )
        {
            //~TO-DO, resize the table
            if(!(table = resize_table(table_size, table)))return NULL;
        }

        node_t* new_entry = NULL;
        if((new_entry = add_front(key, value, &(chain_head))))
        {
            number_entries++;
            printf("\n\nkey: %s, new_entry was returned: \n", new_entry->key);
            printf("chain_head->key %s\n", chain_head->key);
            printf("%s\n", "calling print_chain:");
            print_chain(chain_head);
            //table[hash_index] = chain_head;
            printf("%s\n", "calling print_table:");
            print_table(table_size, table);
            printf("\n%s\n", "Unless I overwrite with table[hash_index] = chain_head, the linked-list chain does not appear to be added to the table correctly.\nI did pass &(chain_head) where chain_head is the node_t* in hash_table[hash_index],\nhash_index is 2 for \"Hello\"\n");
            return new_entry;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        current->value += value;
        return current;
    }
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