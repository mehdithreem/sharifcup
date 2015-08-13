#include "Graph.h"

Graph::Graph() :_size(0) {}

void Graph::addComponent (vector<MovingObj>& obstacles){
	int penalty = _size;

	for(int i=0 ; i<obstacles.size() ; i++){
		nodes.insert(nodes.end() , obstacles[i].coords.begin() , obstacles[i].coords.end());
		vector<int> temp{penalty + 1, penalty + obstacles[i].coords.size() - 1};
		list.push_back(temp);
		for(int j=penalty+1 ; j<obstacles[i].coords.size()+penalty ; j++){
			vector<int> temp2{j+1,j-1};
			list.push_back(temp2);
		}
		penalty += obstacles[i].coords.size();
	}
	_size = penalty;
	matrix.resize(_size);
	for(int i=0 ; i<matrix.size() ; i++){
		matrix[i].resize(_size,-1);
		for(int j=0 ; j<matrix[i].size() ; j++)
			if(matrix[i][j]==-1)
				matrix[i][j] = (nodes[i] - nodes[j]).size();
	}

}

		 
void addSingleNode(geometry::vector newNode);







// Graph::Graph(vector<vector<geometry::Vector> > coords){

// 	size = 0;
	
// 	for(int i=0 ; i<coords.size() ; i++)
// 		size += coords[i].size();

// 	matrix.resize(size, vector<double>(size,0));
// 	list.resize(size);

// 	int penalty = 0;
// 	for(int j = 0; j < coords.size(); j++) {
// 		for(int i = penalty + 1; i < coords[j].size() + penalty; i++) 
// 			nodes.push_back(coords[j][i - penalty]);

// 			matrix[i][i-1] = (nodes[i]-nodes[i-1]).size();
// 			matrix[i-1][i] = (nodes[i]-nodes[i-1]).size();

// 			list[i].push_back(i-1);
// 			list[i-1].push_back(i);
// 		}

// 		matrix[penalty][penalty + coords[j].size()-1] = true;
// 		matrix[penalty + coords[j].size()-1][penalty] = true;


// 		list[penalty].push_back(penalty + coords[j].size()-1);
// 		list[penalty + coords[j].size()-1].push_back(penalty);

// 		penalty += coords[j].size(); 
// 	}
// } 



