Graph::Graph(vector<vector<geometry::Vector> > coords){

	size = 0;
	
	for(int i=0 ; i<coords.size() ; i++)
		size += coords[i].size();

	matrix.resize(size, vector<double>(size,0));
	list.resize(size);

	int penalty = 0;
	for(int j = 0; j < coords.size(); j++) {
		for(int i = penalty + 1; i < coords[j].size() + penalty; i++) 
			nodes.push_back(coords[j][i - penalty]);

			matrix[i][i-1] = (nodes[i]-nodes[i-1]).size();
			matrix[i-1][i] = (nodes[i]-nodes[i-1]).size();

			list[i].push_back(i-1);
			list[i-1].push_back(i);
		}

		matrix[penalty][penalty + coords[j].size()-1] = true;
		matrix[penalty + coords[j].size()-1][penalty] = true;


		list[penalty].push_back(penalty + coords[j].size()-1);
		list[penalty + coords[j].size()-1].push_back(penalty);

		penalty += coords[j].size(); 
	}
} 

void Graph :: addNode(){
	vector<int> temp;
	list.push_back(temp);
	for(int i=0 ; i<matrix.size() ; i++)
		matrix[i].push_back(false);
	size++;
	vector<bool> temp2(size,false);
	matrix.push_back(temp2);
}
