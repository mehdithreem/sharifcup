all: out
out: main.o MovingObj.o ShortestPath.o geometry.o Graph.o Vision.o
	g++ -O2 -o out main.o MovingObj.o ShortestPath.o geometry.o Graph.o Vision.o
main.o: main.cpp ./Core/MovingObj.h ./Vision/Vision.h ./Pathfinding/ShortestPath.h ./Utility/Graph.h ./Utility/geometry.h
	g++ -O2 -c main.cpp
MovingObj.o: ./Core/MovingObj.cpp ./Core/MovingObj.h ./Utility/geometry.h
	g++ -O2 -c ./Core/MovingObj.cpp
ShortestPath.o: ./Pathfinding/ShortestPath.cpp ./Pathfinding/ShortestPath.h ./Core/MovingObj.h ./Utility/geometry.h ./Utility/Graph.h
	g++ -O2 -c ./Pathfinding/ShortestPath.cpp
geometry.o: ./Utility/geometry.cpp ./Utility/geometry.h
	g++ -O2 -c ./Utility/geometry.cpp
Graph.o: ./Utility/Graph.cpp ./Utility/Graph.h ./Core/MovingObj.h
	g++ -O2 -c ./Utility/Graph.cpp
Vision.o: ./Vision/Vision.cpp ./Vision/Vision.h ./Core/MovingObj.h
	g++ -O2 -c ./Vision/Vision.cpp
