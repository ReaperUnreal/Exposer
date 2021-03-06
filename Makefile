CC=g++
CFLAGS=-c -Wall -fopenmp -march=core2
LFLAGS=-fopenmp
EXECUTABLE=exposer
EASY_BMP_CFLAGS=-c -fopenmp -O3 -march=core2 -mrecip

all: CFLAGS+=-O3 -DOMP_ENABLE -ffast-math -fprefetch-loop-arrays -funsafe-loop-optimizations -fno-signed-zeros -fno-trapping-math -fassociative-math -freciprocal-math -mrecip
all: $(EXECUTABLE)

debug: CFLAGS+=-g
debug: $(EXECUTABLE)

$(EXECUTABLE): basicfilters.o EasyBMP.o filter.o image.o log.o main.o night.o sigmoid.o
	$(CC) $(LFLAGS) basicfilters.o EasyBMP.o filter.o image.o log.o main.o night.o sigmoid.o -o $(EXECUTABLE)

basicfilters.o: basicfilters.cpp
	$(CC) $(CFLAGS) basicfilters.cpp

EasyBMP.o: EasyBMP.cpp
	$(CC) $(EASY_BMP_CFLAGS) EasyBMP.cpp

filter.o: filter.cpp
	$(CC) $(CFLAGS) filter.cpp

image.o: image.cpp
	$(CC) $(CFLAGS) image.cpp

log.o: log.cpp
	$(CC) $(CFLAGS) log.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

night.o: night.cpp
	$(CC) $(CFLAGS) night.cpp

sigmoid.o: sigmoid.cpp
	$(CC) $(CFLAGS) sigmoid.cpp

clean:
	\rm -rf *.o $(EXECUTABLE)
