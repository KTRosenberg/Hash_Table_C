Work-in-progress hash-table with separate chaining and table resizing

caution: code needs additional testing.

Compile (in this case using gcc) with:

    gcc -g -Wall -Wextra hashtable.c -c -o table.o

    gcc -g -Wall -Wextra hashchain.c -c -o chain.o

    gcc -g -Wall -Wextra table.o chain.o -o program_name
