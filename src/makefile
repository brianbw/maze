
# Make file for disjointSets 

OBJS	= testDSclass.o disjointSets.o
OBJS1	= maze.o mazeGenerator.o
CC	= g++ -Wall -pedantic -g -std=c++11
DEPS	= disjointSets.h
DEPS1 	= mazeGenerator.h

all: testDSclass maze

disjointSets.o: disjointSets.cpp $(DEPS)
	$(CC) -c disjointSets.cpp

mazeGenerator.o: mazeGenerator.cpp $(DEPS1)
	$(CC) -c mazeGenerator.cpp

testDSclass: $(OBJS) $(DEPS)
	$(CC) -o testDSclass $(OBJS)

testDSclass.o: testDSclass.cpp $(DEPS)
	$(CC) -c testDSclass.cpp

maze: $(OBJS1) $(DEPS1) $(DEPS)
	$(CC) -o maze $(OBJS1) disjointSets.o

maze.o: maze.cpp $(DEPS) $(DEPS1)
	$(CC) -c maze.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS) $(OBJS1)

