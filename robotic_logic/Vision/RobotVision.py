__author__ = 'Ali'
import cv2
import numpy as np

def drawPoints(points,imageName):
	for currPoint in points :
		cv2.circle(imageName,currPoint,2,(0,0,255),thickness=2)


def nothing(x):
	pass
#in RGB
initialLowerBound = (40,40,100)
initialUpperBound = (120,120,255)

cv2.namedWindow("frame")
cv2.createTrackbar("noise reductin amount","frame",5,15,nothing)
cv2.createTrackbar("object size","frame",60,100,nothing)
cv2.createTrackbar("lred","frame",initialLowerBound[0],255,nothing)
cv2.createTrackbar("mred","frame",initialUpperBound[0],255,nothing)
cv2.createTrackbar("lgreen","frame",initialLowerBound[1],255,nothing)
cv2.createTrackbar("mgreen","frame",initialUpperBound[1],255,nothing)
cv2.createTrackbar("lblue","frame",initialLowerBound[2],255,nothing)
cv2.createTrackbar("mblue","frame",initialUpperBound[2],255,nothing)
# create video capture
cap = cv2.VideoCapture(0)

while(1):
	kernelSize = cv2.getTrackbarPos("noise reductin amount","frame")
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
	_,frame = cap.read()
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
					print "area of curr max " + "%f" % area
			++i
			
		if(cv2.contourArea(maxContour) > objectSizeThresh):
			print "area of max max ! " + "%f" % cv2.contourArea(maxContour)
			print "contour size :"
			print len(contours)

			points= cv2.convexHull(maxContour)
			print "points are :"
			print points
			cv2.drawContours(frame,[points],0,(0,0,255),thickness=2)

			rect= cv2.minAreaRect(maxContour)
			box = cv2.boxPoints(rect)
			box = np.int0(box)
			cv2.drawContours(frame,[box],0,(0,0,255),thickness=2)
			print "box :"
			print box



	# M = cv2.moments(best_cnt)
	# cx,cy = int(M['m10']/M['m00']), int(M['m01']/M['m00'])
	# cv2.circle(frame,(cx,cy),5,255,-1)
	# Show it, if key pressed is 'Esc', exit the loop
	cv2.imshow('frame',frame)
	cv2.imshow('threshOrig',threshOrig)
	cv2.imshow('threshMorpho',threshMorpho)
	# cv2.imshow('threshMorpho',threshMorpho)
	if cv2.waitKey(33)== 27:
		break

# Clean up everything before leaving
cv2.destroyAllWindows()
cap.release()
