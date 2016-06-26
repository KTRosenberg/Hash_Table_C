hash-table implementation with separate chaining and automatic table resizing

allows the user to specify his or her own hash function when initializing a hash table

to-do: 
possibly user input,
improve resizing (providing an array of prime numbers is an option)

Compile as individual object files and create executable
(in this case using gcc) with (for example):

    gcc -g -Wall -Wextra hashtable.c -c -o table.o

    gcc -g -Wall -Wextra hashchain.c -c -o chain.o

    gcc -g -Wall -Wextra main1.c -c -o main1.o

    gcc -g -Wall -Wextra table.o chain.o main1.o -o programname

A makefile for main1 and main2 is also available.

run <make> or <make test1> to compile test1,
which creates a small hash table and tests
put, get, and remove functions

run <make test2> to compile test2,
which reads the text file words.txt (a large list of words),
puts them in the hash table, and displays the table
(pass a command line argument of 'x' to avoid displaying the table)
