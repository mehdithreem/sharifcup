import sys
import pygame

constant = 1

BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
BLUE =  (  0,   0, 255)
GREEN = (  0, 255,   0)
RED =   (255,   0,   0)

print "Prepare window ..."

pygame.init()
screen = pygame.display.set_mode((350*1,350*1))
screen.fill(WHITE)
pygame.display.set_caption("VisGraph")

if 'inString' not in locals() or 'inString' not in globals():
	print "Called independently"
	inString = open("input").read()

inString = inString.split('\n')

if inString[-1] == '':
	inString = inString[:-1]

for line in inString:
	if line[-1] == ' ':
		line = line[:-1]
		
	line = line.split(' ')
	
	mode = line[0]
	if mode == 'C' or mode == 'O':
		color = RED
	elif mode == 'R':
		color = BLACK
	elif mode == 'L':
		color = BLUE
	else: 
		color = GREEN

	line = line[1:]

	for i, point in enumerate(line):
		point = point.split(',')
		line[i] = [int(float(point[0]))*constant, int(float(point[1]))*constant]
		pygame.draw.circle(screen, color, line[i], 3)

	if mode is 'C':
		pygame.draw.lines(screen ,color ,True ,line)
	elif mode is 'O':
		pygame.draw.polygon(screen ,color ,line)
	elif mode is 'R':
		pygame.draw.polygon(screen ,color ,line)
	elif mode is 'L':
		pygame.draw.lines(screen ,color ,False ,line)

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