__author__ = 'Ali'
import cv2
import numpy as np
import math

def nothing(x):
	pass

def drawPoints(frame,points):
	for currPoint in points :
		cv2.circle(frame,(currPoint[0][0],currPoint[0][1]),2,(0,0,255),thickness=2)

def angle2(point1,point2):
	return math.degrees(math.atan2(point1[1] - point2[1],point1[0]-point2[0]))

def angle3(point1,centerPoint,point2):
	P12 = math.sqrt( math.pow( (point1[0]-point2[0]) , 2) + math.pow( (point1[1]-point2[1]) , 2) )
	P1c = math.sqrt( math.pow( (point1[0]-centerPoint[0]) , 2) + math.pow( (point1[1]-centerPoint[1]) , 2) )
	P2c = math.sqrt( math.pow( (point2[0]-centerPoint[0]) , 2) + math.pow( (point2[1]-centerPoint[1]) , 2) )
	radian = math.acos( (math.pow(P1c,2) + math.pow(P2c,2) - math.pow(P12,2)) / (2*P2c*P1c) )
	return math.degrees(radian)
	# degree1 = angle2(point1,centerPoint)
	# degree2 = angle2(point2,centerPoint)
	# return math.fabs(degree2 - degree1)

def getHeadPointIndex(points):
	degree1 = angle3(points[0][0],points[1][0],points[2][0])
	degree2 = angle3(points[1][0],points[2][0],points[0][0])
	degree3 = angle3(points[2][0],points[0][0],points[1][0])
	if(degree1 < degree2 and degree1 < degree3) :
		return 1
	if(degree2 < degree1 and degree2 < degree3) :
		return 2
	if(degree3 < degree1 and degree3 < degree2) :
		return 0

def getMiane(headPointIndex,points):
	otherPoints = []
	for i in range(3) :
		if(i!=headPointIndex) :
			otherPoints.append(points[i][0])
	point1 = otherPoints[0]
	point2 = otherPoints[1]
	x = ( point1[0] + point2[0] )/2
	y = ( point1[1] + point2[1] )/2
	return [x,y]

#in RGB
initialLowerBound = (0,0,0)
initialUpperBound = (66,71,85)
intialNoiseReduction =  1
intialHoleFilling =  1
initialShapeDetail = 20

cv2.namedWindow("frame")
cv2.createTrackbar("shape detail","frame",initialShapeDetail,100,nothing)
cv2.createTrackbar("noise reduction","frame",intialNoiseReduction,15,nothing)
cv2.createTrackbar("hole filling","frame",intialHoleFilling,15,nothing)
cv2.createTrackbar("object size","frame",0,100,nothing)
cv2.createTrackbar("lred","frame",initialLowerBound[0],255,nothing)
cv2.createTrackbar("mred","frame",initialUpperBound[0],255,nothing)
cv2.createTrackbar("lgreen","frame",initialLowerBound[1],255,nothing)
cv2.createTrackbar("mgreen","frame",initialUpperBound[1],255,nothing)
cv2.createTrackbar("lblue","frame",initialLowerBound[2],255,nothing)
cv2.createTrackbar("mblue","frame",initialUpperBound[2],255,nothing)
# create video capture
cap = cv2.VideoCapture(0)

while(1):
	shapeDetail =(float)(cv2.getTrackbarPos("shape detail","frame")) / 200
	kernelSizeNoise = cv2.getTrackbarPos("noise reduction","frame")
	kernelSizeHole = cv2.getTrackbarPos("hole filling","frame")
	objectSizeThresh = cv2.getTrackbarPos("object size","frame")
	objectSizeThresh = (objectSizeThresh/2)*1000
	lBlue = cv2.getTrackbarPos("lblue","frame")
	mBlue = cv2.getTrackbarPos("mblue","frame")
	lGreen = cv2.getTrackbarPos("lgreen","frame")
	mGreen = cv2.getTrackbarPos("mgreen","frame")
	lRed = cv2.getTrackbarPos("lred","frame")
	mRed = cv2.getTrackbarPos("mred","frame")

	lowerBound = np.array((lBlue,lGreen,lRed))
	upperBound = np.array((mBlue,mGreen,mRed))
	print upperBound

	_,frame = cap.read()
	# frame = frame[50:430]
	# frame = cv2.blur(frame,(3,3))

	frame = cv2.resize(frame,(0,0),fx=0.5,fy=0.5)


	# lowerBound = (cv2.cvtColor(lowerBound,cv2.COLOR_RGB2HSV))[0][0]
	# upperBound = (cv2.cvtColor(upperBound,cv2.COLOR_RGB2HSV))[0][0]
	# print lowerBound
	# print upperBound
	# hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
	threshOrig = cv2.inRange(frame,lowerBound, upperBound)
	thresh = threshOrig.copy()

	# #morphological opening (remove small objects from the foreground)
	kernelNoise = np.ones((kernelSizeNoise,kernelSizeNoise),np.uint8)
	kernelHole = np.ones((kernelSizeHole,kernelSizeHole),np.uint8)
	threshMorpho = cv2.morphologyEx(thresh,cv2.MORPH_OPEN,kernelNoise)
	threshMorpho = cv2.morphologyEx(threshMorpho,cv2.MORPH_CLOSE,kernelHole)

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
			print "area of max max ! " + "%f" % cv2.contourArea(maxContour)
			# print "contour size :"
			print len(contours)

			# points = cv2.convexHull(maxContour)
			# print "points are :"
			# print points
			# cv2.drawContours(frame,[points],0,(0,0,255),thickness=1)
			# drawPoints(frame,points)

			# rect= cv2.minAreaRect(maxContour)
			# print "angle is  :"
			# print rect[2]
			# box = cv2.boxPoints(rect)
			# box = np.int0(box)
			# cv2.drawContours(frame,[box],0,(0,0,255),thickness=2)
			# print "box :"
			# print box


			arcLength = cv2.arcLength(maxContour,True)
			print "arcLength is :"
			print arcLength
			points = cv2.approxPolyDP(maxContour,shapeDetail*arcLength,True)
			cv2.drawContours(frame,[points],0,(0,0,255),thickness=1)
			drawPoints(frame,points)
			print "points are :"
			print points
			moments = cv2.moments(maxContour)
			centerPoint = (int(moments['m10']/moments['m00']) , int(moments['m01']/moments['m00']))
			cv2.circle(frame,centerPoint,2,(0,0,255),thickness=2)
			print "center point is :"
			print centerPoint
			#for degree
			if (len(points) == 3):
				print "TRIANGLE RECOGNIZED SUCCESSFULLY"
				headPointIndex = getHeadPointIndex(points)
				headPoint = points[headPointIndex][0]
				miane = getMiane(headPointIndex,points)
				degree = angle2(miane,headPoint)
				print "degree is :"
				print degree
				cv2.arrowedLine(frame,(miane[0],miane[1]),(headPoint[0],headPoint[1]),(0,255,0),thickness=2,tipLength=0.2)
			else :
				print "WARNIG : CAN'T RECOGNIZE TRIANGLE !"
	# M = cv2.moments(best_cnt)
	# cx,cy = int(M['m10']/M['m00']), int(M['m01']/M['m00'])
	# cv2.circle(frame,(cx,cy),5,255,-1)
	# Show it, if key pressed is 'Esc', exit the loop
	cv2.imshow('frame',frame)
	cv2.imshow('threshOrig',threshOrig)
	cv2.imshow('threshMorpho',threshMorpho)
	if cv2.waitKey(33)== 27:
		break

# Clean up everything before leaving
cv2.destroyAllWindows()
cap.release()
