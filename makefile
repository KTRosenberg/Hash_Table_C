CC     = gcc
CFLAGS = -O3 -g -Wall -Wextra
OBJS = hashtable.o hashchain.o main1.o
OBJS2 = hashtable.o hashchain.o main2.o
OBJS3 = hashtable.o hashchain.o main3.o

test1 : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test1

test2 : $(OBJS2)
	$(CC) $(CFLAGS) $(OBJS2) -o test2

test3 : $(OBJS3)
	$(CC) $(CFLAGS) $(OBJS3) -o test3

hashtable.o : hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c hashtable.c

hashchain.o : hashchain.c hashchain.h
	$(CC) $(CFLAGS) -c hashchain.c

main1.o : main1.c hashtable.h
	$(CC) -c main1.c

main2.o : main2.c hashtable.h
	$(CC) -c main2.c

main3.o : main3.c hashtable.h
	$(CC) -c main3.c

clean :
	-rm -f *.o *.core

