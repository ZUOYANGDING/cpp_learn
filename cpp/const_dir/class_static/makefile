test: main.o classroom.o classroom.h
	g++ -g -o test main.o classroom.o
main.o: main.cpp classroom.h
	g++ -g -c main.cpp
classroom.o: classroom.cpp classroom.h
	g++ -g -c classroom.cpp

clean:
	rm *.o test