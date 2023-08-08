COMPILER = g++


vector3-test: vector3.cpp vector3.test.cpp
	@${COMPILER} -c vector3.cpp vector3.test.cpp
	@${COMPILER} vector3.o vector3.test.o -o vector3-test.out
	@if ./vector3-test.out; then \
		echo All Vector3 tests passed.; \
	fi

hvector-test: hvector.cpp hvector.test.cpp
	@${COMPILER} -c hvector.cpp hvector.test.cpp
	@${COMPILER} vector3.o hvector.o hvector.test.o -o hvector-test.out
	@if ./hvector-test.out; then \
		echo All HVector tests passed.; \
	fi

transform-test: transform.cpp transform.test.cpp
	@${COMPILER} -c transform.cpp transform.test.cpp
	@${COMPILER} vector3.o hvector.o transform.o transform.test.o -o transform-test.out
	@if ./transform-test.out; then \
		echo All Transform tests passed.; \
	fi

test: -vector3-test -hvector-test -transform-test clean

clean:
	@rm -f *.out *.o

MAKEFLAGS += --no-print-directory

-%:
	-@$(MAKE) $*
