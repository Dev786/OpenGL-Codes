import cv2
import numpy as np

cap = cv2.VideoCapture(0)
fourcc = cv2.VideoWriter_fourcc('M','J','P','G')
outColored = cv2.VideoWriter('colored.avi',fourcc,60,(640,480))
while True:
    ret,frame = cap.read()
    #for gray image
    gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    cv2.imshow("COLORED",frame)
    cv2.imshow("BLACK AND WHITE",gray)
    outColored.write(frame)
    outBlack.write(gray)
    if(cv2.waitKey(1)==27):
        break

    