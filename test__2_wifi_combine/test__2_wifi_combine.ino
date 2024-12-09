#include <SoftwareSerial.h>

SoftwareSerial esp8266(2,3); //make RX,TX pin

#define DEBUG true
#define enA 10//Enable1 L298 Pin enA 
#define in1 6 //Motor1  L298 Pin in1 
#define in2 7 //Motor2  L298 Pin in2 
#define in3 8 //Motor3  L298 Pin in3 
#define in4 9 //Motor4  L298 Pin in4 
#define enB 11//Enable2 L298 Pin enB 
const int speed = 100;
//Color Sensor pins
const int s0 = 4; //Conection for Sensor
const int s1 = 5;

//for left
const int s2L = A0;
const int s3L = A1;
const int outL = A2;
int redL = 0; //Left color sensor values
int greenL = 0;
int blueL = 0;

//for right
const int s2R = A3;
const int s3R = A4;
const int outR = A5;
int redR = 0; //Right color sensor values
int greenR = 0;
int blueR = 0;

int sensor_left = 0;
int sensor_right = 0;

String color = "";
String colorToReturn = "";

void setup()
{
  Serial.begin(9600); //Serial communication
  esp8266.begin(9600);
  //MOTOR PINS
  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
  pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 
  //analogWrite(enA, 200); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
  //analogWrite(enB, 200); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
  //COLOR Sensor 
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  pinMode(s2L, OUTPUT);
  pinMode(s3L, OUTPUT);
  pinMode(outL, INPUT);

  pinMode(s2R, OUTPUT);
  pinMode(s3R, OUTPUT);
  pinMode(outR, INPUT);

  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point and stationary
  sendData("AT+CWJAP=\"AustonMMCampus\",\"helloyangon\"\r\n",5000,DEBUG); //connect wifi
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}

void loop()
{
  if(esp8266.available()) // check if the esp is sending a message
  {
    if(esp8266.find("+IPD,"))
    {
      delay(1000);// wait for the serial buffer to fill up (read all the serial data)
      int connectionId = esp8266.read() - '0';// get the connection id so that we can then disconnect
      esp8266.find("color=");
      // Read until either a space or carriage return is encountered
      color = esp8266.readStringUntil(' ');
      esp8266.readStringUntil('\n');

      Serial.print("Received color: ");
      Serial.println(color);

      while(color == "red")
      {
        ColorDetect();
        //forward();
        //delay(100);
        Red();
        Direction();
        colorToReturn = "red";
        receiveInfo();
      }
      while(color =="green")
      {
        ColorDetect();
        //turnLeft();
        //delay(500);
        //forward();
        //delay(100);
        Green();
        Direction();
        colorToReturn = "green";
        receiveInfo();
      }
      while(color=="blue")
      {
        ColorDetect();
        //turnRight();
        //delay(500);
        //forward();
        //delay(100);
        Blue();
        Direction();
        colorToReturn = "blue";
        receiveInfo();
      }
      if(color == "yellow")
      {
        turnRight();
        delay(1200);
        while(1)
        {
          ReturnHome(colorToReturn);
          receiveInfo();
        }
      }
      // make close command
      String closeCommand = "AT+CIPCLOSE="; 
      closeCommand+=connectionId; // append connection id
      closeCommand+="\r\n";

      sendData(closeCommand,1000,DEBUG); // close connection
    }
  }
}

void receiveInfo()
{
  if(esp8266.available()) // check if the esp is sending a message
  {
    if(esp8266.find("+IPD,"))
    {
      delay(1000);// wait for the serial buffer to fill up (read all the serial data)
      int connectionId = esp8266.read() - '0';// get the connection id so that we can then disconnect
      esp8266.find("color=");
      // Read until either a space or carriage return is encountered
      color = esp8266.readStringUntil(' ');
      esp8266.readStringUntil('\n');

      Serial.print("Received color: ");
      Serial.println(color);
      // make close command
      String closeCommand = "AT+CIPCLOSE="; 
      closeCommand+=connectionId; // append connection id
      closeCommand+="\r\n";

      sendData(closeCommand,1000,DEBUG); // close connection
    }
  }
}
/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";    
  esp8266.print(command); // send the read character to the esp8266   
  long int time = millis();    
  while( (time+timeout) > millis())
  {
    while(esp8266.available())
    {        
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      response+=c;
    }  
  }    
  if(debug)
  {Serial.print(response);}    
  return response;
}

void ReturnHome(String colorToReturn)
{
  
  ColorDetect();
  Serial.print("Color: ");
  Serial.print(colorToReturn);
  if(colorToReturn == "red"){Red();}
  else if(colorToReturn == "green"){Green();}
  else if(colorToReturn == "blue"){Blue();}
  Direction();
}
//Read color values
void ColorDetect() 
{
  { //Left Sensor
    digitalWrite(s2L, LOW);
    digitalWrite(s3L, LOW);
    redL = pulseIn(outL, digitalRead(outL) == HIGH ? LOW : HIGH);
    digitalWrite(s3L, HIGH);
    blueL = pulseIn(outL, digitalRead(outL) == HIGH ? LOW : HIGH);
    digitalWrite(s2L, HIGH);
    greenL = pulseIn(outL, digitalRead(outL) == HIGH ? LOW : HIGH);
    //redL = map(redL,101,107,255,0);
    //greenL = map(greenL,152,162,255,0);
    //blueL = map(blueL,118,127,255,0);
  }
  { //Right Sensor
    digitalWrite(s2R, LOW);
    digitalWrite(s3R, LOW);
    redR = pulseIn(outR, digitalRead(outR) == HIGH ? LOW : HIGH);
    digitalWrite(s3R, HIGH);
    blueR = pulseIn(outR, digitalRead(outR) == HIGH ? LOW : HIGH);
    digitalWrite(s2R, HIGH);
    greenR = pulseIn(outR, digitalRead(outR) == HIGH ? LOW : HIGH);
  }
}

//color detection
void Red()
{ //Sensor Left
  if (redL <= 20 && greenL >= 20 && blueL >= 15 && redL < blueL && redL < greenL)
  //if(redL >= 50 && redL <= 80 && greenL >= 150 && greenL <= 190 && blueL >= 110 && blueL <= 130)
  {sensor_left = 1;}
  else
  {sensor_left = 0;}

  //Sensor Right
  if (redR <= 20 && greenR >= 20 && blueR >= 15 && redR < blueR && redR < greenR)
  //if(redR >= 50 && redR <= 80 && greenR >= 190 && greenR <= 230 && blueR >= 130 && blueR <= 160)
  {sensor_right = 1;}
  else
  {sensor_right = 0;}
}

void Green()
{  //Sensor Left
  if (greenL <= 15 && redL >=12 && blueL >= 6 && greenL < redL)
  {sensor_left = 1;}
  else
  {sensor_left = 0;}
  
  //Sensor Right
  if (greenR <= 23 && redR >= 14 && blueR >= 13 && greenR < redR)
  {sensor_right = 1;}
  else
  {sensor_right = 0;}
}

void Blue()
{
  //Sensor Left
  if (blueL <= 25 && redL >= 30 && greenL >= 23 && blueL < redL && blueL < greenL)
  {sensor_left = 1;}
  else
  {sensor_left = 0;}

  //Sensor Right
  if (blueR <= 35 && redR >= 32 && greenR >= 32 && blueR < redR && blueR < greenR)
  {sensor_right = 1;}
  else
  {sensor_right = 0;}
}

void Yellow()
{
  //if(redL >= 6 && redL <= 15 && greenL >=  && greenL <=  && blueL >=  && blueL <= )
  if(redL <= 15 && greenL >= 8 && blueL >= 8 && redL < greenL && redL < blueL)
  {sensor_left = 2;}
  else
  {sensor_left = 0;}
  //if(redR >=  && redR <=  && greenR >=  && greenR <=  && blueR >=  && blueR <= )
  if(redR <= 15 && greenR >= 8 && blueR >= 10 && redR < greenR && redR < blueR)
  {sensor_right = 2;}
  else
  {sensor_right = 0;}
}

void Direction()
{ //Direction 
  if (sensor_left ==1 or sensor_right==1)
  {
    Found:
    if (sensor_left == 1 && sensor_right == 1)
    {//forward
      forward();
      delay(50);
      stop();
      Serial.println("Going forward ");
    }
    else if (sensor_left == 0 && sensor_right == 1)
    {//Right Curve
      turnRight();
      delay(50);
      stop();
      Serial.println("Turning Right");
    }
    else if (sensor_left == 1 && sensor_right == 0)
    {//Left Curve
      turnLeft();
      delay(50);
      stop();
      Serial.println("Turning Left"); 
    }
  } 
  else if (sensor_left == 0 && sensor_right == 0)
  {
    stop();
    delay(500);
    backward();
    delay(100);
    stop();
    Serial.println("Color detection ERROR!NO LINE DETECTED");  
  }
}
//MOTOR
void forward()
{
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enA, speed);

 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 analogWrite(enB, speed);
}
void backward()
{
 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 analogWrite(enA, speed);

 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 analogWrite(enB, speed);
}
void turnRight()
{
 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 analogWrite(enA, speed);

 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 analogWrite(enB, speed);
}
void turnLeft()
{
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enA, speed);

 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 analogWrite(enB, speed);
}
void stop()
{
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);
} 
