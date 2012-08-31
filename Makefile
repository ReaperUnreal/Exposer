CC=g++
CFLAGS=-c -Wall -fopenmp -march=core2
LFLAGS=-fopenmp
EXECUTABLE=exposer
EASY_BMP_CFLAGS=-c -fopenmp -O3 -march=core2 -mrecip

all: CFLAGS+=-O3 -DOMP_ENABLE -ffast-math -fprefetch-loop-arrays -funsafe-loop-optimizations -fno-signed-zeros -fno-trapping-math -fassociative-math -freciprocal-math -mrecip
all: $(EXECUTABLE)

debug: CFLAGS+=-g
debug: $(EXECUTABLE)

$(EXECUTABLE): EasyBMP.o main.o
	$(CC) $(LFLAGS) EasyBMP.o main.o -o $(EXECUTABLE)

EasyBMP.o: EasyBMP.cpp
	$(CC) $(EASY_BMP_CFLAGS) EasyBMP.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	\rm -rf *.o $(EXECUTABLE)
