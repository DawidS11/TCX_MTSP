CC = g++
CFLAGS = -Wall -g

main: main.o GA.o Population.o Tour.o City.o
	$(CC) $(CFLAGS) -o main main.o GA.o Population.o Tour.o City.o

main.o: main.cpp GA.hpp Population.hpp Tour.hpp City.hpp
	$(CC) $(CFLAGS) -c main.cpp

GA.o: GA.hpp Population.hpp Tour.hpp City.hpp

Population.o: Population.hpp Tour.hpp City.hpp

Tour.o: Tour.hpp City.hpp

City.o: City.hpp

clean:
	rm -f main
