test:main.o person.o person.h
	g++ -g -o test main.o person.o
main.o: main.cpp person.h
	g++ -g -c main.cpp
person.o: person.cpp person.h
	g++ -g -c person.cpp

clean:
	rm *.o test