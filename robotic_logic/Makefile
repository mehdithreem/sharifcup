all: out
out: main.o MovingObj.o geometry.o
	c++ -O2 -o out main.o MovingObj.o geometry.o
main.o: main.cpp MovingObj.h Vision.h ShortestPath.h
	c++ -O2 -c main.cpp 
MovingObj.o: MovingObj.cpp MovingObj.h geometry.h
	c++ -O2 -c MovingObj.cpp
geometry.o: geometry.cpp geometry.h
	c++ -O2 -c geometry.cpp
clean: -rm *.o
