CC=g++

CFLAGS= -c -Wall -std=c++11

all: pencrypt

pencrypt: pencrypt.o particals.o ParticalRandomGenerator.o
	$(CC) pencrypt.o particals.o ParticalRandomGenerator.o -o pencrypt

pencrypt.o: pencrypt.cpp
	$(CC) $(CFLAGS) pencrypt.cpp
	
particals.o: particals.cpp
	$(CC) $(CFLAGS) particals.cpp
	
ParticalRandomGenerator.o: ParticalRandomGenerator.cpp
	$(CC) $(CFLAGS) ParticalRandomGenerator.cpp
clean:
	rm -rf *.o core.* pencrypt


