#include "ShortestPath.h"
#include "../Utility/Graph.h"
#include <set>
#include <vector>
#include <limits>
#include <cmath>

vector<int> constructPath(std::vector<int>& parent, int goal, int start);
int heuristic(int start, int goal, Graph& G);


// Comprator for heap used in a-star algorithm
struct openSetGreater{

	openSetGreater(std::vector<double>* _key) {
		key = _key;
	}

	std::vector<double>* key;

	bool operator()(int& a, int& b) const{
		return key->at(a) > key->at(b);
	}
};

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, vector<MovingObj>& obstacles , MovingObj& rival ) {
	
	Graph G;

	G.addSingleNode(start);
	G.addSingleNode(goal);

	obstacles.push_back(rival);
	G.addComponent(obstacles);
	obstacles.pop_back();

	VisibiltyGraph(G);

	std::vector<geometry::Vector> path;

	try {
		std::vector<int> pathIndex = AStar(0, 1, G);

		for (int i = pathIndex.size() - 1; i >= 0 ; i--)
			path.push_back(G.nodes[pathIndex[i]]);

	} catch (...) {
		// no path found!!
		// use a random direction to pathfind again
	}

	return path;
}

vector<int> AStar(int start , int goal ,Graph& G)
{
	std::set<int> closedSet;
	std::vector<int> openSet;

	std::vector<double> gScore(G.size(), std::numeric_limits<double>::max());
	std::vector<double> fScore(G.size(), std::numeric_limits<double>::max());
	std::vector<int> parent(G.size());

	gScore[start] = 0;
	fScore[start] = gScore[start] + heuristic(start, goal, G);

	openSet.push_back(start);
	std::make_heap(openSet.begin(), openSet.end(), openSetGreater(&fScore));

	while (openSet.size() > 0) {
		std::pop_heap(openSet.begin(),openSet.end(), openSetGreater(&fScore));
		int curr = openSet.back();

		if (curr == goal)
			return constructPath(parent, goal, start);

		openSet.pop_back();
		closedSet.insert(curr);

		for (int i = 0; i < G.list[curr].size(); i++) {
			int neighbor = G.list[curr][i];

			if (closedSet.find(neighbor) != closedSet.end())
				continue;

			double tempGScore = gScore[curr] + G.matrix[curr][neighbor];

			if (find(openSet.begin(), openSet.end(), neighbor) == openSet.end()
				|| tempGScore < gScore[neighbor]) {
				parent[neighbor] = curr;
				gScore[neighbor] = tempGScore;
				fScore[neighbor] = gScore[neighbor] + heuristic(curr, neighbor, G);

				if (find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
					openSet.push_back(neighbor);
					std::push_heap (openSet.begin(),openSet.end(),openSetGreater(&fScore));
				}
			}
		}
	}

	throw "Can't construct path";
	return std::vector<int>();
}


int heuristic(int start, int goal, Graph& G)
{
	return abs(G.nodes[start].x - G.nodes[goal].x) + abs(G.nodes[start].y - G.nodes[goal].y);
}

vector<int> constructPath(std::vector<int>& parent, int goal, int start)
{
	vector<int> path;
	path.push_back(goal);

	while (true) {
		path.push_back(parent[goal]);
		goal = parent[goal];
		if (goal == start)
			break;
	}

	return path;
}

void VisibiltyGraph(Graph& graph) { return; }
