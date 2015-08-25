#include <Python.h>
#include "../Include/Graph.h"
#include "../Include/geometry.h"
#include "../Include/ShortestPath.h"
// #include "/usr/local/include/polyclipping/clipper.hpp"
#include "../Include/clipper.h"

void graphTest(int argc, char *argv[])
{
	Graph testG;

	// testG.print();

	MovingObj agent;
	{
		geometry::Vector v(5,3.5);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(100,100));
		vertices.push_back(geometry::Vector(120,120));
		vertices.push_back(geometry::Vector(120,100));
		vertices.push_back(geometry::Vector(100,120));

		agent.update(v, vertices);
	}
	testG.addSingleNode(agent.COM);

	MovingObj rival;
	{
		geometry::Vector v(5,3.5);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(300,300));
		vertices.push_back(geometry::Vector(320,320));
		vertices.push_back(geometry::Vector(320,300));
		vertices.push_back(geometry::Vector(300,320));

		rival.update(v, vertices);
	}

	std::vector<MovingObj> obstacles;

	obstacles.push_back(MovingObj());

	{	geometry::Vector v(10,10);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(1*15,1*15));
		vertices.push_back(geometry::Vector(3*15,2*15));
		vertices.push_back(geometry::Vector(2*15,5*15));

		obstacles[obstacles.size()-1].update(v, vertices);
	}
	
	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(5,3.5);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(9*15,8*15));
		vertices.push_back(geometry::Vector(16*15,9*15));
		vertices.push_back(geometry::Vector(10*15,11*15));
		vertices.push_back(geometry::Vector(12*15,12*15));

		obstacles[obstacles.size()-1].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(7.5,8);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(11*15,3*15));
		vertices.push_back(geometry::Vector(14*15,6*15));
		vertices.push_back(geometry::Vector(14*15,3*15));
		vertices.push_back(geometry::Vector(11*15,6*15));

		obstacles[obstacles.size()-1].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(11,3.4);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(19*15,3*15));
		vertices.push_back(geometry::Vector(17*15,4*15));
		vertices.push_back(geometry::Vector(16*15,5*15));
		vertices.push_back(geometry::Vector(21*15,7*15));
		vertices.push_back(geometry::Vector(21*15,8*15));
		vertices.push_back(geometry::Vector(16*15,7*15));

		obstacles[obstacles.size()-1].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{
		geometry::Vector v(10,7);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(4*15,12*15));
		vertices.push_back(geometry::Vector(3*15,10*15));
		vertices.push_back(geometry::Vector(3*15,11*15));
		vertices.push_back(geometry::Vector(6*15,8*15));
		vertices.push_back(geometry::Vector(6*15,11*15));

		obstacles[obstacles.size()-1].update(v, vertices);
	}

	
	obstacles.push_back(MovingObj());

	{	geometry::Vector v(10,10);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(140,200));
		vertices.push_back(geometry::Vector(180,240));
		vertices.push_back(geometry::Vector(140,280));
		vertices.push_back(geometry::Vector(100,240));
		vertices.push_back(geometry::Vector(150,230));
		vertices.push_back(geometry::Vector(150,250));
		vertices.push_back(geometry::Vector(130,230));
		vertices.push_back(geometry::Vector(130,250));

		obstacles[obstacles.size()-1].update(v, vertices);
	}

	obstacles.push_back(MovingObj());

	{	geometry::Vector v(10,10);
		std::vector<geometry::Vector> vertices;

		vertices.push_back(geometry::Vector(240,200));
		vertices.push_back(geometry::Vector(280,240));
		vertices.push_back(geometry::Vector(240,280));
		vertices.push_back(geometry::Vector(200,240));
		vertices.push_back(geometry::Vector(210,210));
		vertices.push_back(geometry::Vector(270,210));
		vertices.push_back(geometry::Vector(270,270));
		vertices.push_back(geometry::Vector(210,270));

		obstacles[obstacles.size()-1].update(v, vertices);
	}
	// obstacles.push_back(MovingObj());

	// {	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	vertices.push_back(geometry::Vector(150,20));
	// 	vertices.push_back(geometry::Vector(190,20));
	// 	vertices.push_back(geometry::Vector(150,60));
	// 	vertices.push_back(geometry::Vector(190,60));

	// 	obstacles[0].update(v, vertices);
	// }

	// obstacles.push_back(MovingObj());

	// {	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	vertices.push_back(geometry::Vector(130,70));
	// 	vertices.push_back(geometry::Vector(200,70));
	// 	vertices.push_back(geometry::Vector(130,130));
	// 	vertices.push_back(geometry::Vector(200,120));

	// 	obstacles[1].update(v, vertices);
	// }

	// obstacles.push_back(MovingObj());

	// {	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	vertices.push_back(geometry::Vector(10,10));
	// 	vertices.push_back(geometry::Vector(30,10));
	// 	vertices.push_back(geometry::Vector(10,50));
	// 	vertices.push_back(geometry::Vector(30,40));

	// 	obstacles[2].update(v, vertices);
	// }

	// obstacles.push_back(MovingObj());

	// {	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	vertices.push_back(geometry::Vector(210,210));
	// 	vertices.push_back(geometry::Vector(260,210));
	// 	vertices.push_back(geometry::Vector(210,260));
	// 	vertices.push_back(geometry::Vector(260,260));

	// 	obstacles[3].update(v, vertices);
	// }

	// obstacles.push_back(MovingObj());

	// {	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	vertices.push_back(geometry::Vector(220,220));
	// 	vertices.push_back(geometry::Vector(250,220));
	// 	vertices.push_back(geometry::Vector(220,250));
	// 	vertices.push_back(geometry::Vector(250,250));

	// 	obstacles[4].update(v, vertices);
	// }

	// obstacles.push_back(MovingObj());

	// {	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	vertices.push_back(geometry::Vector(230,230));
	// 	vertices.push_back(geometry::Vector(240,230));
	// 	vertices.push_back(geometry::Vector(230,240));
	// 	vertices.push_back(geometry::Vector(240,240));

	// 	obstacles[5].update(v, vertices);
	// }

	// ClipperLib::Path pattern;
	// ClipperLib::Paths subj(1), clip(2), minsum;
	// ClipperLib::PolyTree solution;
	
	// //define outer blue 'subject' polygon
	// subj[0] << 
	// 	ClipperLib::IntPoint(-(10-20),-(10-30)) << ClipperLib::IntPoint(-(30-20),-(10-30)) <<
	// 	ClipperLib::IntPoint(-(10-20),-(50-30)) << ClipperLib::IntPoint(-(30-20),-(40-30));

	// pattern << 
	// 	ClipperLib::IntPoint(-(80-120),-(200-175)) << ClipperLib::IntPoint(-(160-120),-(200-175)) <<
	// 	ClipperLib::IntPoint(-(160-120),-(150-175)) << ClipperLib::IntPoint(-(80-120),-(150-175));
	
	// //define orange 'clipping' polygon
	// clip[0] << 
	// 	ClipperLib::IntPoint(130,70) << ClipperLib::IntPoint(200,70) << 
	// 	ClipperLib::IntPoint(130,130) << ClipperLib::IntPoint(200,120);

	// clip[1] << 
	// 	ClipperLib::IntPoint(150,20) << ClipperLib::IntPoint(190,20) << 
	// 	ClipperLib::IntPoint(150,60) << ClipperLib::IntPoint(190,60);
	

	// //perform intersection ...
	// ClipperLib::Clipper c;
	// c.AddPaths(subj, ClipperLib::ptSubject, true);
	// c.AddPaths(clip, ClipperLib::ptClip, true);
	// c.Execute(ClipperLib::ctUnion, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

	// // perform minkowski sum
	// // MinkowskiSum(const Path& pattern, const Paths& paths, Paths& solution, bool pathIsClosed);
	// ClipperLib::MinkowskiSum(subj[0], clip, minsum, true);

	// ClipperLib::PolyNode* currNode = solution.GetFirst();

	// while(currNode != NULL){
	// 	obstacles.push_back(MovingObj());

	// 	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	for (int i = 0; i < currNode->Contour.size(); ++i)
	// 	{
	// 		vertices.push_back(geometry::Vector(currNode->Contour[i].X+100, currNode->Contour[i].Y+100));
	// 	}
		
	// 	obstacles[obstacles.size()-1].update(v, vertices);

	// 	currNode = currNode->GetNext();
	// }

	// obstacles.push_back(MovingObj());
	// {
	// 	geometry::Vector v(10,10);
	// 	std::vector<geometry::Vector> vertices;

	// 	for (int i = 0; i < minsum[0].size(); ++i)
	// 	{
	// 		vertices.push_back(geometry::Vector(minsum[0][i].X, minsum[0][i].Y));
	// 	}
		
	// 	obstacles[obstacles.size()-1].update(v, vertices);
	// }

	std::vector<MovingObj> finalObstacles;
	finalObstacles = MinkowskiAll(agent, rival, obstacles);

	testG.addComponent(finalObstacles);

	testG.addSingleNode(geometry::Vector(10,300));

	VisibiltyGraph(testG);

	// cerr << "before visualize" << endl;
	std::vector<int> path;
	path = AStar(0 , testG.size()-1 ,testG);

	testG.visualize(argc, argv, path, agent, rival, obstacles);

	return;
}

int main(int argc, char *argv[]) {

	graphTest(argc, argv);

	return 0;
}
