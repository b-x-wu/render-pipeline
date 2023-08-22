COMPILER = g++

# TODO: move the math stuff to its own library/module/something

vector3-test: vector3.cpp vector3.test.cpp
	@${COMPILER} -c vector3.cpp vector3.test.cpp
	@${COMPILER} vector3.o vector3.test.o -o vector3-test.out
	@if ./vector3-test.out; then \
		echo All Vector3 tests passed.; \
	fi

color-test: color.hpp color.test.cpp
	@${COMPILER} -c color.test.cpp
	@${COMPILER} color.test.o -o color-test.out
	@if ./color-test.out; then \
		echo All Color tests passed.; \
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

primitive-test: primitive.cpp primitive.test.cpp
	@${COMPILER} -c primitive.cpp primitive.test.cpp
	@${COMPILER} vector3.o hvector.o primitive.o primitive.test.o -o primitive-test.out
	@if ./primitive-test.out; then \
		echo All Primitive tests passed.; \
	fi

camera-test: camera.cpp camera.test.cpp
	@${COMPILER} -c camera.cpp camera.test.cpp
	@${COMPILER} vector3.o hvector.o transform.o primitive.o camera.o camera.test.o -o camera-test.out
	@if ./camera-test.out; then \
		echo All Camera tests passed.; \
	fi

vertex-shader-test: vertex-shader.cpp vertex-shader.test.cpp
	@${COMPILER} -c vertex-shader.cpp vertex-shader.test.cpp
	@${COMPILER} vector3.o hvector.o transform.o primitive.o camera.o vertex-shader.o vertex-shader.test.o -o vertex-shader-test.out
	@if ./vertex-shader-test.out; then \
		echo All VertexShader tests passed.; \
	fi

test: -vector3-test -color-test -hvector-test -transform-test -primitive-test -camera-test -vertex-shader-test clean

clean:
	@rm -f *.out *.o

MAKEFLAGS += --no-print-directory

-%:
	-@$(MAKE) $*
