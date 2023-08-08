COMPILER = g++

vector3-test: vector3.cpp vector3.test.cpp
	@${COMPILER} -c vector3.cpp vector3.test.cpp
	@${COMPILER} vector3.o vector3.test.o -o vector3-test.out
	@if ./vector3-test.out; then \
		echo All tests passed.; \
	fi

test: vector3-test clean

clean:
	@rm -f *.out *.o

