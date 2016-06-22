hash-table implementation with separate chaining and automatic table resizing

allows the user to specify his or her own when initializing a hash table

to-do: 
text file input and possibly user input,
improve resizing (providing an array of prime numbers is an option)

Compile as individual object files and create executable
(in this case using gcc) with:

    gcc -g -Wall -Wextra hashtable.c -c -o table.o

    gcc -g -Wall -Wextra hashchain.c -c -o chain.o

    gcc -g -Wall -Wextra main1.c -c -o main1.o

    gcc -g -Wall -Wextra table.o chain.o main1.o -o programname