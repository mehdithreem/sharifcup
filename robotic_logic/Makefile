all: out
out: main.o ./Core/MovingObj.o ShortestPath.o geometry.o Graph.o Vision.o
	g++ -O2 -o out main.o ./Core/MovingObj.o ShortestPath.o geometry.o Graph.o Vision.o
main.o: main.cpp ./Core/./Core/MovingObj.h ./Vision/Vision.h ./Pathfinding/ShortestPath.h ./Utility/Graph.h ./Utility/geometry.h
	g++ -O2 -c main.cpp
./Core/MovingObj.o: ./Core/MovingObj.cpp ./Core/MovingObj.h ./Utility/geometry.h
	g++ -O2 -c ./Core/MovingObj.cpp
ShortestPath.o: ShortestPath.cpp ShortestPath.h ./Core/MovingObj.h ./Utility/geometry.h ./Utility/Graph.h
	g++ -O2 -c ShortestPath.cpp
geometry.o: geometry.cpp geometry.h
	g++ -O2 -c geometry.cpp
Graph.o: Graph.cpp Graph.h ./Core/MovingObj.h
	g++ -O2 -c Graph.h
Vision.o: Vision.cpp Vision.h ./Core/MovingObj.h
	g++ -O2 -c Vision.cpp
