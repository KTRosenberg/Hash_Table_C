Work-in-progress hash-table with separate chaining and table resizing

to-do: user input, rewrite to use a hash_table struct that contains the table, 
its size, and the number of entries

caution: code needs additional testing.

Compile (in this case using gcc) with:

    gcc -g -Wall -Wextra hashtable.c -c -o table.o

    gcc -g -Wall -Wextra hashchain.c -c -o chain.o

    gcc -g -Wall -Wextra table.o chain.o -o program_name
