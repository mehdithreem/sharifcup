import sys
import pygame

constant = 1

BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
BLUE =  (  0,   0, 255)
GREEN = (  0, 255,   0)
RED =   (255,   0,   0)
MAG = (255, 0, 255)
BROWN = (42, 33, 9)
YELLOW = (255, 255, 0)
LBROWN = (72, 65, 45)

print "Prepare window ..."

pygame.init()
screen = pygame.display.set_mode((494*constant,404*constant))
screen.fill(BROWN)
pygame.display.set_caption("VisGraph")

if 'inString' not in locals() or 'inString' not in globals():
	print "Called independently"
	inString = open("input").read()

print inString

inString = inString.split('\n')

if inString[-1] == '':
	inString = inString[:-1]

Obstacles = list()
Robot = list()
Lines = list()
Convex = list()
ShortestPath = list()
Points = list()


for line in inString:
	if line[-1] == ' ':
		line = line[:-1]
		
	line = line.split(' ')
	mode = line[0]
	line = line[1:]

	for i, point in enumerate(line):
		point = point.split(',')
		line[i] = [int(float(point[0]))*constant, int(float(point[1]))*constant]
		Points.append(line[i])

	if mode == 'C':
		Convex.append(line)
	elif mode == 'O':
		Obstacles.append(line)
	elif mode == 'R':
		Robot.append(line)
	elif mode == 'L':
		Lines.append(line)	
	elif mode == 'P':
		ShortestPath.append(line)

for line in Obstacles:
	if len(line) <= 2: continue
	pygame.draw.polygon(screen ,YELLOW ,line)

for line in Robot:
	pygame.draw.polygon(screen ,WHITE ,line)

for line in Lines:
	pygame.draw.aalines(screen ,LBROWN ,False ,line, 2)

for line in Convex:
	pygame.draw.aalines(screen ,YELLOW ,True ,line, 3)

for line in ShortestPath:
	pygame.draw.lines(screen ,MAG , True, line, 5)

for point in Points:
	pygame.draw.circle(screen,YELLOW ,point, 4)

done = False
clock = pygame.time.Clock()
 
while not done:
 
	# This limits the while loop to a max of 10 times per second.
	# Leave this out and we will use all CPU we can.
	clock.tick(10)

	for event in pygame.event.get(): # User did something
		if event.type == pygame.QUIT: # If user clicked close
			done=True

	pygame.display.flip()

pygame.quit()