C = gcc
CFLAGS = -Wall -pedantic
DEST_FOLDER = out/

main: main.c database.o bank.o
	$(C) $(CFLAGS) -o main main.c bank.o directory.o database.o

directory.o: directory.c
	$(C) $(CFLAGS) -c directory.c 
database.o: database.c directory.c
	$(C) $(CFLAGS) -c database.c directory.c
bank.o: bank.c database.c
	$(C) $(CFLAGS) -c bank.c database.c

clean:
	rm *.o