test: main.o student.o
	g++ -g -o test main.o student.o
main.o: main.cpp student.h
	g++ -g -c main.cpp
student.o: student.cpp student.h
	g++ -g -c student.cpp

clean:
	rm *.o test