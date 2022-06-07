test: main.o employee.o
	g++ -g -o test main.o employee.o
main.o: employee.o employee.h main.cpp base.h
	g++ -g -c main.cpp
employee.o: employee.cpp base.h employee.h
	g++ -g -c employee.cpp
clean:
	rm *.o test