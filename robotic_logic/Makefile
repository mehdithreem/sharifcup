all: out
out: main.o MovingObj.o ShortestPath.o geometry.o Graph.o Vision.o
	g++ -std=c++11 -O2 -o out main.o MovingObj.o ShortestPath.o geometry.o Graph.o Vision.o -lpython2.7
main.o: main.cpp ./Include/MovingObj.h ./Include/Vision.h ./Include/ShortestPath.h ./Include/Graph.h ./Include/geometry.h
	g++ -std=c++11 -O2 -c main.cpp
MovingObj.o: ./Core/MovingObj.cpp ./Include/MovingObj.h ./Include/geometry.h
	g++ -std=c++11 -O2 -c ./Core/MovingObj.cpp
ShortestPath.o: ./Pathfinding/ShortestPath.cpp ./Include/ShortestPath.h ./Include/MovingObj.h ./Include/geometry.h ./Include/Graph.h
	g++ -std=c++11 -O2 -c ./Pathfinding/ShortestPath.cpp
geometry.o: ./Utility/geometry.cpp ./Include/geometry.h
	g++ -std=c++11 -O2 -c ./Utility/geometry.cpp
Graph.o: ./Utility/Graph.cpp ./Include/Graph.h ./Include/MovingObj.h
	g++ -std=c++11 -I/usr/include/python2.7/ -lpython2.7 -O2 -c ./Utility/Graph.cpp
Vision.o: ./Vision/Vision.cpp ./Include/Vision.h ./Include/MovingObj.h
	g++ -std=c++11 -O2 -c ./Vision/Vision.cpp
