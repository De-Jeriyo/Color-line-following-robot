//#include <SoftwareSerial.h>
//#include <Servo.h>
//Servo myServo;
//SoftwareSerial Serial1(2,3); //make RX,TX pin

#define DEBUG true
#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor2  L298 Pin in2 
#define in3 7 //Motor3  L298 Pin in3 
#define in4 6 //Motor4  L298 Pin in4 
#define enB 11//Enable2 L298 Pin enB 
const int speed = 90;
//Color Sensor pins
const int s0 = 4; //Conection for Sensor
const int s1 = 5;

//for left
const int s2L = A4;
const int s3L = A5;
const int outL = A3;
int redL = 0; //Left color sensor values
int greenL = 0;
int blueL = 0;

//for right

const int s2R = A1;
const int s3R = A2;
const int outR = A0;
int redR = 0; //Right color sensor values
int greenR = 0;
int blueR = 0;

int sensor_left = 0;
int sensor_right = 0;
int yellow_left = 0;
int yellow_right = 0;

String color = "";
String colorToReturn = "";

void setup()
{
  Serial.begin(9600); //Serial communication
  //Serial1.begin(9600);
  Serial1.begin(115200);
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

  //myServo.attach(12);
  //myServo.write(0);
  //Serial.print("Hello");

  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point and stationary
  sendData("AT+CWJAP=\"AustonMMCampus\",\"helloyangon\"\r\n",5000,DEBUG); //connect wifi
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  while(!Serial1.available());
  receiveInfo();
}

void loop()
{
  if(color == "red" || color == "green" || color == "blue")
  {
    LeaveHome();
    colorToReturn = color;
    while(color != "yellow"){ColorDetect();executeColor(color);Direction();FoundYellow();}
  }
  if(color == "yellow")
  {
    Serial.print("ColorToReturn: ");
    Serial.print(colorToReturn);
    while(color == "yellow"){ReturnHome(colorToReturn);}
  }
}

//-----------------------------------------------------WI-FI----------------------------------------------------//
//**********FUNCTION TO CHECK WHETHER ESP IS RECEVING INFOMATION OR NOT*******//
void receiveInfo()
{
  if(Serial1.available()) // check if the esp is sending a message
  {
    if(Serial1.find("+IPD,"))
    {
      delay(1000);// wait for the serial buffer to fill up (read all the serial data)
      int connectionId =Serial1.read() - '0';// get the connection id so that we can then disconnect
      Serial1.find("color=");
      // Read until either a space or carriage return is encountered
      color =Serial1.readStringUntil(' ');
      Serial1.readStringUntil('\n');

      Serial.print("Received color: ");
      Serial.println(color);

        // Close the connection
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId;
      closeCommand += "\r\n";
      sendData(closeCommand, 1000, DEBUG);
    }
  }
}

//************FUNCTION TO GET IP ADDRESS TO DISPLAY***************//
String getIPaddress()
{
  String response = sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  // Look for the "+CIFSR:STAIP" in the response
  int startIP = response.indexOf("+CIFSR:STAIP");

  // If found, extract the IP address
  if (startIP != -1) {
    startIP = response.indexOf(',', startIP) + 2;
    int endIP = response.indexOf("\r\n", startIP);
    return response.substring(startIP, endIP);
  } else {
    return ""; // Return an empty string if not found
  }
}

/* Name: sendData
* Description: Function used to send data to Serial1.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the Serial1 (if there is a reponse)*/
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";    
  Serial1.print(command); // send the read character to the Serial1   
  long int time = millis();    
  while( (time+timeout) > millis())
  {
    while(Serial1.available())
    {        
      // The esp has data so display its output to the serial window 
      char c = Serial1.read(); // read the next character.
      response+=c;
    }  
  }    
  if(debug)
  {Serial.print(response);}    
  return response;
}
//----------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------CONTROL MECHANISM------------------------------------------------------//
//*******************FUNCTION TO RETURN HOME******************//
void ReturnHome(String colorToReturn)
{
  while(sensor_left == 0 && sensor_right == 0)
  {
    ColorDetect();
    executeColor(colorToReturn);
    turnRight();//delay(100);
  }
  while(color == "yellow")
  {
   ColorDetect();
   executeColor(colorToReturn);
   Direction();FoundYellowHome();
  }
}

//*****************FUNCTION TO LEAVE HOME*******************//
/*void LeaveHome()
{
  //myServo.write(110);
  if(color == "red" && colorToReturn == "red"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnRight();delay(50);}forward();delay(300);}
  else if(color == "red" && colorToReturn == "green"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnLeft();delay(50);}forward();delay(300);}
  else if(color == "red" && colorToReturn == "blue"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnRight();delay(50);}forward();delay(300);}
  else if(color == "green" && colorToReturn == "red"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Green();turnRight();delay(50);}forward();delay(300);}
  else if(color == "green" && colorToReturn == "green"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Green();turnLeft();delay(50);}forward();delay(300);}
  else if(color == "green" && colorToReturn == "blue"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Green();forward();delay(50);}forward();delay(300);}
  else if(color == "blue" && colorToReturn == "red"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Blue();turnLeft();delay(50);}forward();delay(300);}
  else if(color == "blue" && colorToReturn == "green"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Blue();forward();delay(50);}forward();delay(300);}
  else if(color == "blue" && colorToReturn == "blue"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Blue();turnRight();delay(50);}forward();delay(300);}
}*/

void LeaveHome()
{
  if(color == "red"){while(sensor_left == 0 && sensor_right == 0){ColorDetect();Red();forward();delay(50);}}
  else if(color == "green"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Green();turnLeft();delay(50);}forward();delay(300);}
  else if(color == "blue"){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Blue();turnRight();delay(50);}forward();delay(300);}
}
//*******************FUNCTION TO EXECUTE ACCORDING TO COLOR********************//
void executeColor(String currentColor)
{
  if(currentColor == "red")Red();
  else if(currentColor == "green")Green();
  else if(currentColor == "blue")Blue();
}

//***********YELLOW FOUND?************//
void FoundYellow()
{
  Yellow();
  if(yellow_left == 1 && yellow_right == 1 && sensor_left == 0 && sensor_right ==0)
  {
    forward();delay(400);
    Serial.println("Reached yellow!STOPPED");
    while(color != "yellow"){stop();receiveInfo();}
  }
  else{return;}
}

/*void FoundYellowHome()
{
  Yellow();
  if(yellow_left == 1 && yellow_right == 1 && sensor_left == 0 && sensor_right == 0)
  {
    forward();delay(400);
    Serial.println("Reached HOME!STOPPED");
    while(color == "yellow"){stop();receiveInfo();}
  }
  else{return;}
}*/
//Parking 
void FoundYellowHome()
{
  Yellow();
  if(yellow_left == 1 && yellow_right == 1 && sensor_left == 0 && sensor_right == 0)
  {
    if(colorToReturn == "red")
    {
      while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnRight();delay(50);}for(int i=0;i<3;i++){ColorDetect();Red();Direction();}backward();delay(700);
    }
    else if(colorToReturn == "green")
    {
      forward();delay(500);
      while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnLeft();delay(50);}backward();delay(300);
    }
    else if(colorToReturn == "blue")
    {
      forward();delay(500);
      while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnRight();delay(50);}backward();delay(300);
    }
  Serial.println("Reached HOME!STOPPED");
  while(color == "yellow"){stop();receiveInfo();}
  }
  else{return;}
}

//*************FUNCTION TO READ COLOR VALUES***********//
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

//*************FUNCTION TO DETECT COLOR[RED/GREEN/BLUE/YELLOW]***************//
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
  if(redL <= 10 && greenL >= 5 && blueL >= 7 && redL < greenL && redL < blueL)
  {yellow_left = 1;}
  else
  {yellow_left = 0;}
  //if(redR >=  && redR <=  && greenR >=  && greenR <=  && blueR >=  && blueR <= )
  if(redR <= 10 && greenR >= 5 && blueR >= 10 && redR < greenR && redR < blueR)
  {yellow_right = 1;}
  else
  {yellow_right = 0;}
}

//***************FUNCTION TO CONTROL DIRECTION*******************//
void Direction()
{ //Direction 
  if (sensor_left ==1 or sensor_right==1)
  {
    Found:
    if (sensor_left == 1 && sensor_right == 1)
    {//forward
      forward();
      //delay(50);
      //stop();
      Serial.println("Going forward ");
    }
    else if (sensor_left == 0 && sensor_right == 1)
    {//Right Curve
      turnRight();
      //delay(50);
      //stop();
      Serial.println("Turning Right");
    }
    else if (sensor_left == 1 && sensor_right == 0)
    {//Left Curve
      turnLeft();
      //delay(50);
      //stop();
      Serial.println("Turning Left"); 
    }
  } 
  else
  {
    stop();
    //delay(200);
    backward();
    //delay(100);
    //stop();
    Serial.println("Color detection ERROR!NO LINE DETECTED");  
  }
}

//***********FUNCTION TO CONTROL MOTORS*************//
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
