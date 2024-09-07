import RPi.GPIO as GPIO
from time import sleep

# Right Motor
in1 = 17
in2 = 27
enA = 4
# Left Motor
in3 = 5
in4 = 6
enB = 13

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


try:
   while(True):
      # Get user Input
      user_input = input()

      # To see users input
      print(user_input)

      if user_input == 'w':
        forward()
        print("Forward")

      elif user_input == 's':
        backward()
        print('Back')

      elif user_input == 'd':
        turnRight()
        print('Right')

      elif user_input == 'a':
        turnLeft()
        print('Left')

      # Press 'c' to exit the script
      elif user_input == 'c':
        stop()
        print('Stop')

# If user press CTRL-C
except KeyboardInterrupt:
  # Reset GPIO settings
  GPIO.cleanup()
  print("GPIO Clean up")
