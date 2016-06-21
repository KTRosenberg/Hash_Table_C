/*
Karl Toby Rosenberg
*/

#include "hashtable.h"

/*
    init_hash_table
        allocates memory and returns a pointer to a new hash_table_t structure
    param:  
        size_t table_size (the desired table size)
        double load_threshold (the maximum load factor for the new hash table)
            if during a put_record() operation
            the load factor is exceeded,
            an attempt is made to resize the table
        hash_table_t* hash_table (the hash table to search)
    return: 
        upon success returns a hash_table_t pointer to the new hash table
        upon error returns NULL
*/
hash_table_t* init_hash_table(size_t table_size, double load_threshold)
{
    hash_table_t* hash_table_new = (hash_table_t*)malloc(sizeof(hash_table_t));
    
    if(!hash_table_new)return NULL;

    hash_table_new->lists = (record_t**)calloc(table_size, sizeof(record_t*));

    if(!(hash_table_new->lists))return NULL;

    hash_table_new->table_size = table_size;
    hash_table_new->max_load = (load_threshold > 0) ? load_threshold : DEFAULTMAXLOAD;

    return hash_table_new; 
}

/*
    hash 
        generates an index based on the given key,
        calculate a valid index with return_index%table_size
        variation of the Jenkins one-at-a-time hash function
    param:
        char* key (the key to hash)
    return:
        uint64_t a positive integer value,
        use to calculate a valid index in an array
*/
uint64_t hash(char* key)
{
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

/*
    resize_table
        creates a new lists array that is 
        twice the size of the one in the given hash table,
        rehashes the records from the original lists array and transfers
        them to the new larger lists array,and transfers the records from the original hash table to the new one,
        the new lists array replaces the old one in the given hash table,
        the old array is freed
    param:
        hash_table_t* hash_table (the hash table to replace)
    return:
        upon success, 0
        otherwise -1
*/
int resize_table(hash_table_t* hash_table) 
{
    if(!hash_table || !(hash_table->lists))return -1;

    //calculate new lists array size
    size_t new_size = (hash_table->table_size << 1);
    
    //allocate memory for the new lists array
    record_t** larger_table = (record_t**)malloc(sizeof(record_t*)*new_size);

    if(!larger_table)return -1;

    uint64_t size = hash_table->table_size;
    uint64_t i = 0;
    record_t* current_list = NULL;
    record_t* to_transfer = NULL;
    uint64_t table_index = 0;
     
    //iterate through each list in the original lists array
    for(; i < size; ++i)
    {
        //for each record in the current list,
        //remove the record from the old list,
        //rehash the record's key and add the record to the larger list
        current_list = (hash_table->lists)[i];
        while(current_list)
        {
            if(!(to_transfer = remove_front(&current_list) ))return -1;
            table_index = hash(to_transfer->key)%new_size;
            to_transfer->next_link = larger_table[table_index];
            larger_table[table_index] = to_transfer;
        }
    }
    //free the old list
    free(hash_table->lists);
    //set the lists array in the given hash table
    //as the new larger list containing the records 
    hash_table->lists = larger_table;
    hash_table->table_size = new_size;

    return 0;
}

/*
    put_record
        given a key and its non-negative value,
        if the key does not yet exist in the hash table,
            adds a key-value record,
        if the key already exists in the hash table,
            increments the value associated with the key by the value
            passed as an argument
    param:  
        char* key (key to add)
        uint64_t value (value to assign or update)
        hash_table_t* hash_table (the hash table to search)
    return: 
        upon success, returns a pointer to the newly-created key-value record
        upon error returns NULL
*/
record_t* put_record(char* key, uint64_t value, hash_table_t* hash_table)
{
    if(!key || !hash_table)return NULL;

    //calculate index using hash function
    uint64_t table_index = hash(key)%(hash_table->table_size);
    
    //set a double record pointer to the start of the correct list in
    //the hash table's lists array to begin traversing the list
    record_t** link_ptr = &(hash_table->lists[table_index]);
    
    //traverse the list until the chosen key is encountered or
    //the end of the list is reached
    while(*link_ptr && strcmp(key, ((*link_ptr)->key)) != 0)
    {
        //repoint the double pointer record to the next record pointer
        link_ptr = &(*link_ptr)->next_link;
    }

    //if the record does not exist,
    //add a new key-value record to the current list,
    //return a pointer to the key-value new record
    if(!(*link_ptr))
    {
        //check whether load factor threshold will be exceeded after the next record is added
        //if so, resize table, rehash record keys and place them in the larger table,
        //then proceed to hash the new record, then place it in the appropriate list in the larger table
        if(NEEDTORESIZE)
        {
            if((resize_table(hash_table) != 0))return NULL;

            //now that the table should have been resized,
            //find the correct index for the new record
            table_index = hash(key)%(hash_table->table_size);
        }

        //add the new record to the hash table by
        //adding it to the front of the appropriate list in the lists array
        record_t* new_record = NULL;
        if(!(new_record = add_front(key, value, &(hash_table->lists[table_index]))))return NULL;
        {
            //update the total number of records in the hash table,
            //return a pointer to the new key-value record
            hash_table->num_records++;
            return new_record;
        }
    }
    //if the key already exists in the table,
    //update its old value (increment the old value by the new value),
    //return a pointer to the key-value record
    else
    {
        (*link_ptr)->value += value;
        return (*link_ptr);
    }
}

/*
    get_value

    param:  
        char* key (key to locate)
        hash_table_t* hash_table (the hash table to search)
    return: 
        if the key exists,
            returns the non-negative value mapped to the given key
        upon error returns -1
*/
int64_t get_value(char* key, hash_table_t* hash_table)
{
    if(!key || !hash_table)return -1;

    //calculate the lists array index using the hash function
    uint64_t table_index = hash(key)%(hash_table->table_size);

    //point the record pointer to the list at the correct table index
    record_t* link = hash_table->lists[table_index];

    //traverse the list until the chosen key is encountered or
    //the end of the list is reached
    while(link && strcmp(key, ((link)->key)) != 0)
    {
        //repoint the record pointer to the next record
        link = link->next_link;
    }

    //if the record does not exist, return -1
    if(!link)return -1;

    //if the record exist, return its non-negative value
    return link->value;
}

/*
    remove_record
        given a key, removes a record from the hash table
    param:  
        char* key (key to remove)
        hash_table_t* hash_table (the hash table to search)
    return: 
        if the key-value record exists,
            removes the record from the hash table,
            returns a pointer to the removed record 
        upon error returns NULL
*/
record_t* remove_record(char* key, hash_table_t* hash_table)
{
    if(!key || !hash_table)return NULL;

    //calculate index using hash function
    uint64_t table_index = hash(key)%(hash_table->table_size);

    //set a double pointer to the list at the hash index    
    record_t** link_ptr = &(hash_table->lists[table_index]);
    
    //traverse the list until the chosen key is encountered or
    //the end of the list is reached
    while(*link_ptr && strcmp(key, ((*link_ptr)->key)) != 0)
    {
        //repoint the double pointer record to the next record pointer
        link_ptr = &(*link_ptr)->next_link;
    }

    //if entry does not exist, return NULL
    if(!(*link_ptr))return NULL;
    
    //otherwise repoint the current pointer from the record-to-remove
    //to the record after the record-to-remove
    /*
        ->[ ]->[ ]
         ^---^
        link_ptr
    */
    record_t* to_remove = *(link_ptr);
    (*link_ptr) = to_remove->next_link;
    
    //un-link the record-to-remove
    to_remove->next_link = NULL;
    //decrement the total number of records in the hash table
    hash_table->num_records--;
    //return the removed entry
    return to_remove;
}

/*
    print_table
        displays the hash table as a list of bracketed lists
    param:  
        hash_table_t* hash_table (the hash table to display)
    return:
        upon success returns 0 
        if nothing to print, returns -1
*/
int print_table(hash_table_t* hash_table)
{
    if(!hash_table || !(hash_table->lists))return -1;
    
    uint64_t i = 0;
    size_t size = hash_table->table_size;
    for(; i < size; ++i)
    {
        //display each list within brackets
        printf("%s %" PRIu64 "\n", "list index", i);
        printf("%s", "{ ");
        if(hash_table->lists[i])
        {   
            //print the list at the current lists index
            print_list(hash_table->lists[i]);
        }
        printf("%s\n", " }");
    }

    return 0;
}

/*
    clear_table
        frees the memory allocated for the lists array in the given hash table
    param:  
        hash_table_t* hash_table (the hash table whose lists array must be freed)
    return:
        void
*/
void clear_table(hash_table_t* hash_table)
{
    //for each list in the hashtable's lists array,
    //free the list
    uint64_t size = hash_table->table_size;
    uint64_t i = 0;
    for(; i < size; ++i)
    {
        del_list(&(hash_table->lists[i]));
    }
    //free the memory allocated for the now-cleared table
    free(hash_table->lists);
    hash_table->lists = NULL;
}

/*
    del_hash_table
        frees the memory allocated for the given hash table
    param:  
        hash_table_t* hash_table (the hash table to free)
    return:
        void
*/
void del_hash_table(hash_table_t* hash_table)
{
    //free the memory allocated for the lists array in the given hash table
    clear_table(hash_table);
    //free the hash table struct
    free(hash_table);
    hash_table = NULL;
}