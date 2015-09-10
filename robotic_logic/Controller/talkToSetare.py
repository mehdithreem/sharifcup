import math
import serial
import cv2
import numpy as np

def drawPoints(points,imageName):
	for currPoint in points :
		cv2.circle(imageName,currPoint,2,(0,0,255),thickness=2)


def nothing(x):
	pass

def getPos():
	#in RGB
	lowerBound = (0,0,00)
	upperBound = (86,80,76)

	# print "here1"

	cap = cv2.VideoCapture(0)

	# print "here2"

	while(1):
		kernelSize = 0
		objectSizeThresh = 0
		objectSizeThresh = (objectSizeThresh/2)*1000
	
		# print "before cap"
		# take picture
		_,frame = cap.read()
		frame = frame[50:430]

		# print "after cap"
		
		frame = cv2.blur(frame,(3,3))
		frame = cv2.resize(frame,(0,0),fx=0.5,fy=0.5)
		# lowerBound = (cv2.cvtColor(lowerBound,cv2.COLOR_RGB2HSV))[0][0]
		# upperBound = (cv2.cvtColor(upperBound,cv2.COLOR_RGB2HSV))[0][0]
		# print lowerBound
		# print upperBound
		# hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
		threshOrig = cv2.inRange(frame,lowerBound, upperBound)
		thresh = threshOrig.copy()

		# #morphological opening (remove small objects from the foreground)
		kernel = np.ones((kernelSize,kernelSize),np.uint8)
		threshMorpho = cv2.morphologyEx(thresh,cv2.MORPH_OPEN,kernel)
		threshMorpho = cv2.morphologyEx(threshMorpho,cv2.MORPH_CLOSE,kernel)

		# threshMorpho = cv2.dilate(threshMorpho,kernel)
		threshMorphoCopy = threshMorpho.copy()
		temp,contours,hierarchy = cv2.findContours(threshMorphoCopy,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
		# cv2.drawContours(frame,contours,-1,(0,0,255),thickness=2)

		if(len(contours) > 0) :
			objects = []
			maxContour = contours[0]
			i=0
			for cnt in contours:
				area = cv2.contourArea(cnt)
				if area > objectSizeThresh :
					if cv2.contourArea(maxContour) < area :
						maxContour = cnt
						# print "area of curr max " + "%f" % area
				++i
				
			if(cv2.contourArea(maxContour) > objectSizeThresh):
				# print "area of max max ! " + "%f" % cv2.contourArea(maxContour)
				# print "contour size :"
				# print len(contours)

				# points= cv2.convexHull(maxContour)
				# print "points are :"
				# print points
				# cv2.drawContours(frame,[points],0,(0,0,255),thickness=2)

				rect= cv2.minAreaRect(maxContour)
				box = cv2.boxPoints(rect)
				box = np.int0(box)
				# cv2.drawContours(frame,[box],0,(0,0,255),thickness=2)
				print "box :"
				print (box[0]+box[1]+box[2]+box[3])/4
				cv2.destroyAllWindows()
				cap.release()
				return (box[0]+box[1]+box[2]+box[3])/4

		# M = cv2.moments(best_cnt)
		# cx,cy = int(M['m10']/M['m00']), int(M['m01']/M['m00'])
		# cv2.circle(frame,(cx,cy),5,255,-1)
		# Show it, if key pressed is 'Esc', exit the loop
			# cv2.imshow('frame',frame)
			# cv2.imshow('threshOrig',threshOrig)
			# cv2.imshow('threshMorpho',threshMorpho)
		# cv2.imshow('threshMorpho',threshMorpho)
		# if cv2.waitKey(33)== 27:
		# 	break

	# Clean up everything before leaving
    

def talkToSetare(velocity, angle, rotation):
	m1 = 255*((-math.sin((45.0-angle)/180*3.14))*velocity / 100.0)
	m2 = 255*((-math.cos((45.0-angle)/180*3.14))*velocity / 100.0)
	m3 = -m1
	m4 = -m2
	e1 = 255 - abs(m1)
	e2 = 255 - abs(m2)
	x = (1.0*e1)/(e1 + e2) 
	m1 += ((x *rotation)/100.0)*255
	m2 += (((1 - x)*rotation)/100.0)*255
	m3 += ((x *rotation)/100.0)*255
	m4 += (((1 - x)*rotation)/100.0)*255
	m1 = math.floor(m1)
	m2 = math.floor(m2)
	m3 = math.floor(m3)
	m4 = math.floor(m4)
	A = 0
	if m1>0 :
		A|=1<<0
	elif m1<0 :
		A|=1<<1
	if m2>0 :
		A|=1<<2
	elif m2<0 :
		A|=1<<3

	if m3>0 :
		A|=1<<4
	elif m3<0 :
		A|=1<<5

	if m4>0 :
		A|=1<<6
	elif m4<0 :
		A|=1<<7

	return abs(m1),abs(m2),abs(m3),abs(m4),A


ser = serial.Serial("/dev/tty.Setareh-DevB")
goal = (300,215)
speed = 50
whileEnd = True
i = 0
# goals = [(310,240),(420,95)]
goals = []

try:
	while whileEnd:
		pos = getPos()
		print "GOAL:" ,goal

		if abs(goal[0]-pos[0])+abs(goal[1]-pos[1]) < 80:
			print "GOAL CHANGED :D"
			goal = goals[i]
			ser.write(chr(115))
			ser.write(chr(0))
			ser.write(chr(0))
			ser.write(chr(0))
			ser.write(chr(0))
			ser.write(chr(0))
			sleep(1)
			i += 1
			if i == len(goals)+1:
				break

		# print "inloop",pos, goal
		angle = math.atan((goal[1]-pos[1])/(goal[0]-pos[0]))*180/math.pi
		# print angle
		m1,m2,m3,m4,A = talkToSetare(speed, 0, 0)
		# print m1,m2,m3,m4,A

		ser.write(chr(115))
		ser.write(chr(int(m1)))
		ser.write(chr(int(m2)))
		ser.write(chr(int(m3)))
		ser.write(chr(int(m4)))
		ser.write(chr(int(A)))

except KeyboardInterrupt:
	print "IN EXCEPT"
	ser.write(chr(115))
	ser.write(chr(0))
	ser.write(chr(0))
	ser.write(chr(0))
	ser.write(chr(0))
	ser.write(chr(0))

ser.write(chr(115))
ser.write(chr(0))
ser.write(chr(0))
ser.write(chr(0))
ser.write(chr(0))
ser.write(chr(0))


