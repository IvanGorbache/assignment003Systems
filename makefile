all: main.o StrList.o StrList

StrList: main.o StrList.o
	gcc -Wall main.o StrList.o -o StrList

my_graph.o: main.c StrList.h
	gcc -c -Wall main.c

StrList.o: StrList.c StrList.h
	gcc -c -Wall StrList.c

clean:
	rm -f *.o StrList