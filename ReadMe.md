hash-table implementation with separate chaining and automatic table resizing

to-do: text file input, possibly user input

caution: code needs additional testing.

Compile as individual object files and create executable
(in this case using gcc) with:

    gcc -g -Wall -Wextra hashtable.c -c -o table.o

    gcc -g -Wall -Wextra hashchain.c -c -o chain.o

    gcc -g -Wall -Wextra main_1.c -c -o main1.o

    gcc -g -Wall -Wextra table.o chain.o main1.o -o programname