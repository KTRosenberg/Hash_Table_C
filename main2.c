/*
Karl Toby Rosenberg

main test program 2

creates a hash table, reads a text file containing words,
(handles UNIX and DOS end-lines), adds all words to the hash table,
displays the table 

*/

#include "hashtable.h"

int main(int argc, char *argv[])
{
    FILE *text = fopen("words.txt", "r");
    
    if(!text)exit(-1);

    //default table size, low load factor of 0.2 for testing, default Jenkins hash function
    hash_table_t* hash_table = init_hash_table(127151, DEFAULTMAXLOAD, DEFAULTHASH);
    if(!hash_table)exit(-1);

    uint64_t word_count = 1;
    char buffer[51];
    char c = '\0';
    while(fgets(buffer, 51, text))
    {
        if(buffer[0] && buffer[strlen(buffer)-1] == '\n')
        {
            buffer[strlen(buffer)-1] = '\0';
        }
        if(buffer[0] && buffer[strlen(buffer)-1] == '\r')
        {
            buffer[strlen(buffer)-1] = '\0';
        }

        put_record(buffer, word_count, hash_table);
        ++word_count;
    }
    fclose(text);

    if(ferror(text))
    {
        printf("%s\n", "ERROR");
        del_hash_table(&hash_table);
        exit(-2);
    }
    
    if(argc == 2 && argv[1][0] == 'p')
    {
        print_table(hash_table);
    }
    
    del_hash_table(&hash_table);

    return 0;
}
