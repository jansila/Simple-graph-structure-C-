# Makefile

# the C++ compiler
CXX     = g++
CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3

ifeq "$(CXXVERSION)" "4.6.3"
	CXXFLAGS += -std=c++0x
else
	CXXFLAGS += -std=c++11
endif

All: all
all: main  

main:	main.cpp Drink.o PrimRec.o
	$(CXX) $(CXXFLAGS) main.cpp Drink.o PrimRec.o -o main		

PrimRec.o:	PrimRec.cpp PrimRec.h 
	$(CXX) $(CXXFLAGS) -c PrimRec.cpp -o PrimRec.o

Drink.o:	Drink.cpp Drink.h
	$(CXX) $(CXXFLAGS) -c Drink.cpp -o Drink.o

deepclean: 
	rm -f *~ *.o main *.exe *.stackdump TwoDArrayMain GraphMain

clean:
	-rm -f *~ *.o *.stackdump

