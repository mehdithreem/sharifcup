#include "../Include/ShortestPath.h"
#include "../Include/Graph.h"
#include <set>
#include <vector>
#include <limits>
#include <cmath>

vector<int> constructPath(std::vector<int>& parent, int goal, int start);
int heuristic(int start, int goal, Graph& G);

void PolyTree2MovingObj(std::vector<MovingObj>& obstacles, ClipperLib::PolyNode* currNode);


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

vector<geometry::Vector> ShortestPath(geometry::Vector start, geometry::Vector goal, Field& F, int argc, char *argv[] ) {
	Graph G;

	std::vector<MovingObj> finalObstacles;
	// finalObstacles = MinkowskiAll(F.agent, F.rival, F.obstacles);
	
	cout << "----after MinkowskiAll" << endl;

	G.addSingleNode(start);
	G.addSingleNode(goal);

	G.addComponent(F.obstacles);

	VisibiltyGraph(G);

	cout << "----after VisibiltyGraph" << endl;

	std::vector<int> pathIndex;
	// G.visualize(argc, argv, pathIndex, F.agent, F.agent, F.obstacles);
	// cin.ignore();
		
	std::vector<geometry::Vector> path;
	
	cout << "----before AStar" << endl;	
	pathIndex = AStar(0, 1, G);
	cout << "----after AStar" << endl;

	for (int i = 0; i < pathIndex.size() ; i++)
		path.push_back(G.nodes[pathIndex[i]]);

	// G.visualize(argc, argv, pathIndex, F.agent, F.agent, F.obstacles);

	cout << "----before return" << endl;
		
	return path;
}

vector<int> AStar(int start , int goal ,Graph& G)
{
	// std::set<int> closedSet;
	std::vector<int> openSet;
	
	std::vector<double> gScore(G.size(), std::numeric_limits<double>::max());
	std::vector<double> fScore(G.size(), std::numeric_limits<double>::max());
	std::vector<int> parent(G.size());
	std::vector<bool> closed(G.size(), false);
	std::vector<bool> opened(G.size(), false);
	
	gScore[start] = 0;
	fScore[start] = gScore[start] + heuristic(start, goal, G);
	
	openSet.push_back(start);
	std::make_heap(openSet.begin(), openSet.end(), openSetGreater(&fScore));
	
	// cerr << "flag1" << endl;
	
	while (openSet.size() > 0) {
		std::pop_heap(openSet.begin(),openSet.end(), openSetGreater(&fScore));
		int curr = openSet.back();
		
		if (curr == goal)
			return constructPath(parent, goal, start);
		
		openSet.pop_back();
		closed[curr] = true;
		// closedSet.insert(curr);
		
		for (int i = 0; i < G.list[curr].size(); i++) {
			int neighbor = abs(G.list[curr][i]);
			
			// if (closedSet.find(neighbor) != closedSet.end())
			// 	continue;
			
			if (closed[neighbor])
				continue;
			
			double tempGScore = gScore[curr] + abs(G.matrix[curr][neighbor]);
			
			// if (find(openSet.begin(), openSet.end(), neighbor) == openSet.end()
			// 	|| tempGScore < gScore[neighbor]) {
			if (!opened[neighbor] || tempGScore < gScore[neighbor]) {
				parent[neighbor] = curr;
				gScore[neighbor] = tempGScore;
				fScore[neighbor] = gScore[neighbor] + heuristic(curr, neighbor, G);
				
				// if (find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
				if (!opened[neighbor]) {
					openSet.push_back(neighbor);
					std::push_heap (openSet.begin(),openSet.end(),openSetGreater(&fScore));
					opened[neighbor] = true;
				}
			}
		}
	}
	
	throw exceptions::NoPath();
	return std::vector<int>();
}


int heuristic(int start, int goal, Graph& G)
{
	// return abs(G.nodes[start].x - G.nodes[goal].x) + abs(G.nodes[start].y - G.nodes[goal].y);
	return 0;
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

void VisibiltyGraph(Graph& graph) {
	for (int i=0 ; i<graph.size() ; i++){
		vector <int> w = VisibileVertices(i,graph);
		
		for (int j=0 ; j<w.size() ; j++)
			graph.addEdge(i,w[j]);
	}
	return;
}

vector <int>  VisibileVertices(int v,Graph& graph){
	vector <int> res;
	for(int i = 0; i<graph.size() ; i++) {
		if(graph.obNum[i+1] != graph.obNum[v+1]){
			bool intersect = false;
			for(int j=0 ; j<graph.size() && !intersect ; j++) {
				for(int k=0 ; k<graph.list[j].size() && !intersect ; k++) {
					if(graph.list[j][k] < 0) {
						intersect = geometry::IsIntersect(graph.nodes[v] , graph.nodes[i] , graph.nodes[j] ,graph.nodes[-graph.list[j][k]]);
					}
				}
			}
			if(!intersect) {
				res.push_back(i);
			}
		}
		else{
			int sp = i+1 , ep = i+1 , obstaclesNum = graph.obNum[i+1];
			bool intersect = false;
			int orient=0;
			while(graph.obNum[sp]==obstaclesNum)
				sp--;
			while(graph.obNum[ep]==obstaclesNum)
				ep++;
			for(int j=sp+1 ; j<ep && !intersect ; j++){
				int o = geometry::sign((graph.nodes[v].x-graph.nodes[i].x)*(graph.nodes[j-1].y-graph.nodes[v].y)-(graph.nodes[v].y-graph.nodes[i].y)*(graph.nodes[j-1].x-graph.nodes[v].x));
				if(orient==0 && o!=0)
					orient=o;
				else
					if(o!=0 && o!=orient)
						intersect = true;
			}
			if(!intersect) {
				res.push_back(i);
			}
		}
	}
	return res;
}

std::vector<MovingObj> MinkowskiAll(const MovingObj& agent, MovingObj& rival, const std::vector<MovingObj>& obstacles)
{
	ClipperLib::Path pattern;
	std::vector<ClipperLib::Paths> obstaclesPaths;
	
	for (geometry::Vector coordinate: agent.coords) {
		pattern << ClipperLib::IntPoint((agent.COM.x - coordinate.x)*10 ,(agent.COM.y - coordinate.y)*10);
	}
	
	for (MovingObj obj: obstacles) {
		ClipperLib::Paths tmpPath(1);
		
		for (geometry::Vector coordinate: obj.coords) {
			tmpPath[0] << ClipperLib::IntPoint(coordinate.x * 10 ,coordinate.y * 10);
		}
		
		obstaclesPaths.push_back(tmpPath);
		
		ClipperLib::MinkowskiSum(pattern, tmpPath, obstaclesPaths[obstaclesPaths.size()-1], true);
	}
	
	for (vector<ClipperLib::Paths>::iterator target = obstaclesPaths.begin(); target != obstaclesPaths.end(); target++) {
		for (vector<ClipperLib::Paths>::iterator object = obstaclesPaths.begin(); object != obstaclesPaths.end(); object++) {
			if (object == target) continue;

			ClipperLib::Clipper c;
			c.AddPaths(*target, ClipperLib::ptSubject, true);
			c.AddPaths(*object, ClipperLib::ptClip, true);

			ClipperLib::Paths result;
			if(c.Execute(ClipperLib::ctUnion, result))
				cout << "SUCCESS" << endl;

			if (result.size() == 1) {
				int _min = min(target - obstaclesPaths.begin(), object-obstaclesPaths.begin()) , _max = max(target-obstaclesPaths.begin() , object-obstaclesPaths.begin());

				 obstaclesPaths[_min] = result;
				obstaclesPaths.erase(obstaclesPaths.begin()+_max);
				--target;
				break;
			}
		}
	}
	
	std::vector<MovingObj> finalObstacles;

	for (int k = 0; k < obstaclesPaths.size(); k++) {
		for (int j = 0; j < obstaclesPaths[k].size(); j++) {
			finalObstacles.push_back(MovingObj());
			{
				geometry::Vector v(10,10);
				std::vector<geometry::Vector> vertices;

				for (int i = 0; i < obstaclesPaths[k][0].size(); ++i)
				{
					double x = obstaclesPaths[k][j][i].X;
					double y = obstaclesPaths[k][j][i].Y;
					vertices.push_back(geometry::Vector(x / 10, y / 10));
				}
				
				finalObstacles[finalObstacles.size()-1].updateConcave(v, vertices);
			}
		}
	}
	
	return finalObstacles;
}

void PolyTree2MovingObj(std::vector<MovingObj>& obstacles, ClipperLib::PolyNode* currNode)
{
	if (currNode == NULL)
		return;
	
	obstacles.push_back(MovingObj());
	geometry::Vector v(0,0);
	std::vector<geometry::Vector> vertices;
	
	for (int i = 0; i < currNode->Contour.size(); ++i)
	{
		vertices.push_back(geometry::Vector(currNode->Contour[i].X/10, currNode->Contour[i].Y/10));
	}
	
	obstacles[obstacles.size()-1].updateConcave(v, vertices);
	
	for (ClipperLib::PolyNode* child: currNode->Childs) {
		cout << "warning: obstacles has child" << endl;
		PolyTree2MovingObj(obstacles, child);
	}
	
	PolyTree2MovingObj(obstacles, currNode->GetNext());
	return;
}

