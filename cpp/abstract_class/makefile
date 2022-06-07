test: main.o cal.o
	g++ -g -o test main.o cal.o
main.o: main.cpp cal.h
	g++ -g -c main.cpp
cal.o: cal.cpp cal.h base.h
	g++ -g -c cal.cpp

clean:
	rm *.o test
