import pygame

ROBOT = 0
OBSTACLE = 1

BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
BLUE =  (  0,   0, 255)
GREEN = (  0, 255,   0)
RED =   (255,   0,   0)
MAG = (255, 0, 255)
BROWN = (42, 33, 9)
YELLOW = (255, 255, 0)
LBROWN = (72, 65, 45)

pygame.init()
screen = pygame.display.set_mode((350*2,350*2))
screen.fill(BROWN)
pygame.display.set_caption("GameField")
myfont = pygame.font.SysFont("monospace", 13)
myfont.set_bold(True)

running = True
DRAW = False
obstacleType = ROBOT
color = YELLOW
currCoordiantes = list()
robots = list()
obstacles = list()
text = "Hit R to draw a Robot and hit O to draw an obstacle."

def drawStatics():
	screen.fill(BROWN)

	screen.blit(myfont.render(text, 1, LBROWN) , (5, 5))
	
	for robot in robots:
		pygame.draw.polygon(screen ,WHITE ,robot)
		for point in robot:
			pygame.draw.circle(screen,YELLOW ,point, 4)

	for obs in obstacles:
		pygame.draw.polygon(screen ,YELLOW ,obs)
		for point in obs:
			pygame.draw.circle(screen,YELLOW ,point, 4)
	
	if len(currCoordiantes) > 1:
		pygame.draw.aalines(screen ,color ,False ,currCoordiantes, 3)

	for point in currCoordiantes:
			pygame.draw.circle(screen,YELLOW ,point, 4)

def robotCode(name, points):
	outCode = "\tMovingObj " + name +";\n\t{\n"
	outCode += "\t\tgeometry::Vector v(0,0);\n\t\tstd::vector<geometry::Vector> vertices;\n\n"

	for point in points:
		outCode += "\t\tvertices.push_back(geometry::Vector(" + str(point[0]/2) + "," + str(point[1]/2) + "));\n"
	outCode += "\n\t\t" + name + """.update(v, vertices);
	}\n\n"""

	return outCode

def obstacleCode(points):
	outCode = """\tobstacles.push_back(MovingObj());

	{
		geometry::Vector v(0,0);
		std::vector<geometry::Vector> vertices;\n\n"""

	for point in points:
		outCode += "\t\tvertices.push_back(geometry::Vector(" + str(point[0]/2) + "," + str(point[1]/2) + "));\n"
	outCode += """\n\tobstacles[obstacles.size()-1].update(v, vertices);\n}\n\n"""

	return outCode

drawStatics()

while running:
	event = pygame.event.poll()
	if event.type == pygame.QUIT:
		running = False

	elif event.type == pygame.MOUSEMOTION:
		if DRAW:
			text = str((event.pos[0]/2,event.pos[1]/2)) + " [" 
			if obstacleType == ROBOT:
				text += "ROBOT"
			else:
				text += "OBSTACLE"

			if len(currCoordiantes) == 0 : text += "] Click on screen to define a point."
			else: text += "] Click Esc to exit draw mode. Use E to erase last point."

			drawStatics()
			pygame.draw.circle(screen,YELLOW ,event.pos, 4)
			if len(currCoordiantes) == 1:
				pygame.draw.aalines(screen ,color ,False ,[currCoordiantes[-1],event.pos], 3)
			elif len(currCoordiantes) >= 2:
				pygame.draw.aalines(screen ,color ,False ,[currCoordiantes[-1],event.pos,currCoordiantes[0]], 3)

	elif event.type == pygame.MOUSEBUTTONDOWN:
		if DRAW:
			currCoordiantes.append(event.pos)

	elif event.type == pygame.KEYDOWN:
		if not DRAW and (event.key == 111 or event.key == 114):
			DRAW = True
			text = "Click on screen to define a point."
			drawStatics()
			if event.key == 111:
				obstacleType = OBSTACLE
				color = YELLOW
			else:
				obstacleType = ROBOT
				color = WHITE

		if DRAW and event.key == 101:
			if len(currCoordiantes) != 0:
				drawStatics()
				if len(currCoordiantes) == 1:
					pygame.draw.circle(screen,YELLOW ,currCoordiantes[0], 4)
				elif len(currCoordiantes) >= 2:
					pygame.draw.aalines(screen ,color ,False ,[currCoordiantes[-2],currCoordiantes[-1],currCoordiantes[0]], 3)
				currCoordiantes = currCoordiantes[:-1]

		if DRAW and event.key == 27:
			DRAW = False

			if len(currCoordiantes) < 3:
				text = "Not enough points for an object. Try again by R or O."

			else:
				text = "Hit R to draw a Robot and hit O to add an obstacle."
				if obstacleType == ROBOT:
					robots.append(currCoordiantes)
				else:
					obstacles.append(currCoordiantes)

			currCoordiantes = list()
			drawStatics()

	pygame.display.flip()

cppCode = """#include <Python.h>
#include "../Include/Graph.h"
#include "../Include/geometry.h"
#include "../Include/ShortestPath.h"
#include "../Include/clipper.h"

void graphTest(int argc, char *argv[])
{
	Graph testG;

	// testG.print();
"""

if len(robots) > 1:
	cppCode += robotCode("agent", robots[0])
	cppCode += "\ttestG.addSingleNode(agent.COM);\n\n"
	cppCode += robotCode("rival", robots[1])

else:
	print "Need exaclty 2 robots"

cppCode += "\tstd::vector<MovingObj> obstacles;\n\n"

for obstacle in obstacles:
	cppCode += obstacleCode(obstacle)

cppCode += """\tstd::vector<MovingObj> finalObstacles;
	finalObstacles = MinkowskiAll(agent, rival, obstacles);

	testG.addComponent(finalObstacles);

	testG.addSingleNode(geometry::Vector(290,290));

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
}"""


print cppCode

pygame.quit()