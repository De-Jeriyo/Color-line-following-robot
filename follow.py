import RPi.GPIO as GPIO
import cv2
from picamera2 import Picamera2
import time
import numpy as np
from servo import Servo
picam2 = Picamera2()

#Pan tilt servos
pan=Servo(pin=13)
tilt=Servo(pin=12)

panAngle=0
tiltAngle=0

pan.set_angle(panAngle)
tilt.set_angle(tiltAngle)

# Right Motor
in1 = 17
in2 = 27
enA = 4
# Left Motor
in3 = 5
in4 = 6
enB = 14

GPIO.setmode(GPIO.BCM)
GPIO.setup(in1,GPIO.OUT)
GPIO.setup(in2,GPIO.OUT)
GPIO.setup(enA,GPIO.OUT)
GPIO.setup(in3,GPIO.OUT)
GPIO.setup(in4,GPIO.OUT)
GPIO.setup(enB,GPIO.OUT)

speedA=GPIO.PWM(enA,100)
speedB=GPIO.PWM(enB,100)
speedA.start(75)
speedB.start(75)

GPIO.output(in1,GPIO.LOW)
GPIO.output(in2,GPIO.LOW)
GPIO.output(in3,GPIO.LOW)
GPIO.output(in4,GPIO.LOW)

def forward():
  GPIO.output(in1,GPIO.HIGH)
  GPIO.output(in2,GPIO.LOW)
  GPIO.output(in4,GPIO.HIGH)
  GPIO.output(in3,GPIO.LOW)


def backward():
  GPIO.output(in1,GPIO.LOW)
  GPIO.output(in2,GPIO.HIGH)
  GPIO.output(in4,GPIO.LOW)
  GPIO.output(in3,GPIO.HIGH)

def turnRight():
  GPIO.output(in1,GPIO.LOW)
  GPIO.output(in2,GPIO.HIGH)
  GPIO.output(in4,GPIO.LOW)
  GPIO.output(in3,GPIO.LOW)

def turnLeft():
  GPIO.output(in1,GPIO.HIGH)
  GPIO.output(in2,GPIO.LOW)
  GPIO.output(in4,GPIO.LOW)
  GPIO.output(in3,GPIO.LOW)  

def stop():
  GPIO.output(in1,GPIO.LOW)
  GPIO.output(in2,GPIO.LOW)
  GPIO.output(in4,GPIO.LOW)
  GPIO.output(in3,GPIO.LOW)


dispW=1280
dispH=720
picam2.preview_configuration.main.size = (dispW,dispH)
picam2.preview_configuration.main.format = "RGB888"
picam2.preview_configuration.controls.FrameRate=30
picam2.preview_configuration.align()
picam2.configure("preview")
picam2.start()
fps=0
pos=(30,60)
font=cv2.FONT_HERSHEY_SIMPLEX
height=1.5
weight=3
myColor=(0,0,255)
track=0

def onTrack1(val):
    global hueLow
    hueLow=val
    print('Hue Low',hueLow)
def onTrack2(val):
    global hueHigh
    hueHigh=val
    print('Hue High',hueHigh)
def onTrack3(val):
    global satLow
    satLow=val
    print('Sat Low',satLow)
def onTrack4(val):
    global satHigh
    satHigh=val
    print('Sat High',satHigh)
def onTrack5(val):
    global valLow
    valLow=val
    print('Val Low',valLow)
def onTrack6(val):
    global valHigh
    valHigh=val
    print('Val High',valHigh)
def onTrack7(val):
    global track
    track=val
    print('Track Value',track)

cv2.namedWindow('myTracker')

cv2.createTrackbar('Hue Low','myTracker',10,179,onTrack1)
cv2.createTrackbar('Hue High','myTracker',20,179,onTrack2)
cv2.createTrackbar('Sat Low','myTracker',100,255,onTrack3)
cv2.createTrackbar('Sat High','myTracker',255,255,onTrack4)
cv2.createTrackbar('Val Low','myTracker',100,255,onTrack5)
cv2.createTrackbar('Val High','myTracker',255,255,onTrack6)
cv2.createTrackbar('Train-0 Track-1','myTracker',0,1,onTrack7)


while True:
    tStart=time.time()
    frame= picam2.capture_array()
    frame=cv2.flip(frame,-1)
    frameHSV=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    cv2.putText(frame,str(int(fps))+' FPS',pos,font,height,myColor,weight)
    lowerBound=np.array([hueLow,satLow,valLow])
    upperBound=np.array([hueHigh,satHigh,valHigh])
    myMask=cv2.inRange(frameHSV,lowerBound,upperBound)
    myMaskSmall=cv2.resize(myMask,(int(dispW/2),int(dispH/2)))
    myObject=cv2.bitwise_and(frame,frame, mask=myMask)
    myObjectSmall=cv2.resize(myObject,(int(dispW/2),int(dispH/2)))
    
    contours,junk=cv2.findContours(myMask,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    if len(contours)>0:
        contours=sorted(contours,key=lambda x:cv2.contourArea(x),reverse=True)
        #cv2.drawContours(frame,contours,-1,(255,0,0),3)
        contour=contours[0]
        x,y,w,h=cv2.boundingRect(contour)
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),3)
        if track==1:
            error=(x+w/2)-dispW/2
            panAngle=panAngle-error/75
            if panAngle>90:
                panAngle=90
            if panAngle<-90:
                panAngle=-90
            if abs(error)>35:
                pan.set_angle(panAngle)
            tiltError=(y+h/2)-dispH/2
            tiltAngle=tiltAngle+tiltError/75
            if tiltAngle>40:
                tiltAngle=40
            if tiltAngle<-90:
                tiltAngle=-90
            if abs(tiltError)>35:
                tilt.set_angle(tiltAngle)
        
    cv2.imshow('Camera',frame)
    cv2.imshow('Mask',myMaskSmall)
    cv2.imshow('My Object',myObjectSmall)
    if cv2.waitKey(1)==ord('q'):
        break
    tEnd=time.time()
    loopTime=tEnd-tStart
    fps=.9*fps + .1*(1/loopTime)
cv2.destroyAllWindows()