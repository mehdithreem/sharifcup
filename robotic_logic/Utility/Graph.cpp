#include "Graph.h"

Graph::Graph() :_size(0) {}

void Graph::addComponent (vector<MovingObj>& obstacles){
	int penalty = _size;

	for(int i=0 ; i<obstacles.size() ; i++){
		nodes.insert(nodes.end() , obstacles[i].coords.begin() , obstacles[i].coords.end());
		
		vector<int> temp;
		temp.push_back(penalty + 1);
		temp.push_back(penalty + obstacles[i].coords.size() - 1);

		list.push_back(temp);
		
		for(int j=penalty+1 ; j<obstacles[i].coords.size()+penalty ; j++){
			vector<int> temp2;
			temp2.push_back(j+1);
			temp2.push_back(j-1);

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

int Graph::size() { return list.size(); }

void Graph::addSingleNode(geometry::Vector newNode) {
	vector<int> dummy;
  list.push_back(dummy);
  
  for(int i=0 ; i<matrix.size() ; i++)
    for(int j=0 ; j<matrix[i].size() ; j++)
      matrix[i].push_back(0);
  
  nodes.push_back(newNode);
  matrix.resize(nodes.size() , vector<double>(nodes.size(),0));
}




