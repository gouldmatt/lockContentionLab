#target: dependencies
#	action

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

output.o: lab2.cpp
	g++  lab2.cpp -std=c++11 -pthread -o method3
	time ./output

clean:
	rm *.o output
