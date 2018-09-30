#target: dependencies
#	action

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

output.o: lab2.cpp
	g++ -std=c++11 lab2.cpp -pthread -o output
	time ./output

clean:
	rm *.o output
