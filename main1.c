/*
Karl Toby Rosenberg

main test program 1

creates a hash table, tests functions, and displays
the table after each hash table operation
*/

#include "hashtable.h"

int main()
{
    //default table size, low load factor of 0.2 for testing, default Jenkins hash function
    hash_table_t* hash_table = init_hash_table(DEFAULTSIZE, 0.2, DEFAULTHASH);
    if(!hash_table)exit(-1);

    //TO-DO: user or text input/output
    
    size_t old_size = hash_table->table_size;

    put_record("Hello", 1, hash_table);
    printf("\n%s\n", "Added <Hello:1>");
    print_table(hash_table);
    printf("\nsize: %lu, number of records: %lu\n", hash_table->table_size, hash_table->num_records);
    if(hash_table->table_size > old_size)
    {
        old_size = hash_table->table_size;
        printf("%s\n", "resized table");
    }
    
    put_record("world", 2, hash_table);
    printf("\n\n%s\n", "Added <world:2>");
    print_table(hash_table);
    printf("\nsize: %lu, number of records: %lu\n", hash_table->table_size, hash_table->num_records);
    if(hash_table->table_size > old_size)
    {
        old_size = hash_table->table_size;
        printf("%s\n", "resized table");
    }

    put_record("Hello", 2, hash_table);
    printf("\n\n%s\n", "updated <Hello:1> to <Hello:3>");
    print_table(hash_table);
    printf("\nsize: %lu, number of records: %lu\n", hash_table->table_size, hash_table->num_records);
    if(hash_table->table_size > old_size)
    {
        old_size = hash_table->table_size;
        printf("%s\n", "resized table");
    }

    remove_record("world", hash_table);
    printf("\n\n%s\n", "removed <world:2>");
    print_table(hash_table);
    printf("\nsize: %lu, number of records: %lu\n", hash_table->table_size, hash_table->num_records);

    
    put_record("Yay", 4, hash_table);
    printf("\n\n%s\n", "Added <Yay:4>");
    print_table(hash_table);
    printf("\nsize: %lu, number of records: %lu\n", hash_table->table_size, hash_table->num_records);
    if(hash_table->table_size > old_size)
    {
        old_size = hash_table->table_size;
        printf("%s\n", "resized table");
    }

    put_record("Hoorah", 5, hash_table);
    printf("\n\n%s\n", "Added <Hoorah:5>");
    print_table(hash_table);
    printf("\nsize: %lu, number of records: %lu\n", hash_table->table_size, hash_table->num_records);
    if(hash_table->table_size > old_size)
    {
        old_size = hash_table->table_size;
        printf("%s\n", "resized table");
    }

    uint64_t yay = get_value("Yay", hash_table);
    printf("\n\nretrieved value for Yay: %" PRIu64 "\n", yay);

    
    printf("\n\n%s\n", "print before final free");
    print_table(hash_table);
    printf("\nFinal size: %lu, Final number of records: %lu\n", hash_table->table_size, hash_table->num_records);
    
    del_hash_table(hash_table);
    print_table(hash_table);
    printf("\n\n%s\n", "Nothing should have printed, as the hash table has been deleted.");
    
    return 0;
}