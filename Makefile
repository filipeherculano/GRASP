OBJS	= graph.o grasp.o main.o
SOURCE	= src/graph.cc src/grasp.cc src/main.cc
HEADER	= include/graph.h include/grasp.h
OUT	= output
CC	= g++
FLAGS	= -g -c -Wall -std=c++14 -I include/
EXEC 	= ./${OUT}
CLEAN 	= rm -f $(OBJS) $(OUT)

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) && ${EXEC} && ${CLEAN}

graph.o: src/graph.cc
	$(CC) $(FLAGS) src/graph.cc 

grasp.o: src/grasp.cc
	$(CC) $(FLAGS) src/grasp.cc 

main.o: src/main.cc
	$(CC) $(FLAGS) src/main.cc 
