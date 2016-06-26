CC     = gcc
CFLAGS = -O3 -g -Wall -Wextra
OBJS = hashtable.o hashchain.o main1.o

test1 : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test1

hashtable.o : hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c hashtable.c

hashchain.o : hashchain.c hashchain.h
	$(CC) $(CFLAGS) -c hashchain.c

main1.o : main1.c hashtable.h
	$(CC) -c main1.c

clean :
	-rm -f *.o *.core

