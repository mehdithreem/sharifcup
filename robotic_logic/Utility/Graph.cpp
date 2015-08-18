#include "Python.h"
#include <sstream>
#include "../Include/Graph.h"

Graph::Graph() :_size(0) {}

void Graph::addEdge(int v ,int u){
  if(matrix[v][u]==0){
    list[v].push_back(u);
    list[u].push_back(v);
  
    matrix[u][v] = (nodes[u]-nodes[v]).size();
    matrix[v][u] = matrix[u][v];
  }
  return;
}


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
		matrix[i].resize(_size,0);
		for(int j=0 ; j<matrix[i].size() ; j++)
			if(matrix[i][j]==0 && find(list[i].begin(), list[i].end(), j) != list[i].end())
				matrix[i][j] = -(nodes[i] - nodes[j]).size();
	}
  return;
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

	_size += 1;
  return;
}


void Graph::printNodes()
{
	cout << "Nodes: ";
	for (int i=0; i < nodes.size(); i++) {
		cout << i << nodes[i] << " ";
	}
	cout << endl;


	return;
}

void Graph::printMatrix()
{
	cout << "Adj matrix:" << endl;

	cout << '\t'; 
	for(int i=0; i < matrix.size(); i++)
		cout << i << '\t';
	cout << endl;

	for(int i=0; i < matrix.size(); i++) {
		cout << i << '\t';
		for(int j=0; j < matrix[i].size(); j++)
			cout << (int) matrix[i][j] << '\t';
		cout << endl;
	}

	return;
}

void Graph::printList() {
	cout << "Adj List:" << endl;
	for(int i=0; i < list.size(); i++){
		cout << i << ": ";
		for(int neighbor : list[i])
			cout << neighbor << " ";
		cout << endl;
	}
}

void Graph::print()
{
	cout << "size: " << _size << " and " << size() << endl;

	printNodes();
	cout << endl;
	printMatrix();
	cout << endl;
	printList();

	return;
}

void Graph::visualize(int argc, char *argv[])
{
	ostringstream out;

	for(int i = 0; i < matrix.size(); i++) {
		for (int j = i; j < matrix[i].size(); j++) {
			// cout << i << "," << j << endl;
			if (matrix[i][j] != 0) {
				if (matrix[i][j] < 0) out << "C ";
				else if (matrix[i][j] > 0) out << "L ";

				out << nodes[i].x << "," << nodes[i].y << " " << nodes[j].x << "," << nodes[j].y << endl;
			}
		}
	}

	Py_Initialize();
	PySys_SetArgv(argc,argv);

	cout << out.str();

	PyObject * cppInString = PyString_FromString(out.str().c_str());

	PyObject * module = PyImport_AddModule("__main__");
	PyObject * dictionary = PyModule_GetDict(module);

	PyDict_SetItemString(dictionary, "inString", cppInString);
	Py_DECREF(cppInString);

	FILE* PythonScriptFile;
	PythonScriptFile = fopen("../Utility/visualizer.py", "r");
	
	if (PythonScriptFile) {
		PyRun_SimpleFile(PythonScriptFile, "../Utility/visualizer.py");
		fclose(PythonScriptFile);
	}

	Py_Finalize();

	return;
}