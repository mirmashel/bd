a.out: main.o avl.o base.o command.o hash.o list.o record.o client.o
	g++ -std=c++11 -O3 -o server main.o avl.o base.o command.o hash.o list.o record.o
	g++ -std=c++11 -O3 -o client client.o
main.o: main.cpp
	g++ -std=c++11 -O3 -c main.cpp
avl.o:avl.cpp
	g++ -std=c++11 -O3 -c avl.cpp
base.o:base.cpp
	g++ -std=c++11 -O3 -c base.cpp
command.o:command.cpp
	g++ -std=c++11 -O3 -c command.cpp
hash.o:hash.cpp
	g++ -std=c++11 -O3 -c hash.cpp
list.o:list.cpp
	g++ -std=c++11 -O3 -c list.cpp
record.o:record.cpp
	g++ -std=c++11 -O3 -c record.cpp
client.o:client.cpp
	g++ -std=c++11 -O3 -c client.cpp
clean:
	rm -f *.o server client a.out a