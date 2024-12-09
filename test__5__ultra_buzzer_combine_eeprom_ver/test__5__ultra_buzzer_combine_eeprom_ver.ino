#include <EEPROM.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);//OLED constructor

//display_wifi
  // '_a_frm3,40', 50x50px
const unsigned char epd_bitmap_wifi [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xf8, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0xf0, 0x0f, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0x00, 
	0x00, 0xe0, 0x03, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x0f, 0x00, 0xe0, 0x01, 0xf8, 0x7f, 0x00, 
	0x1e, 0x00, 0x78, 0x00, 0xff, 0xff, 0x03, 0x78, 0x00, 0x3c, 0xe0, 0x0f, 0xc0, 0x1f, 0xf0, 0x00, 
	0x0e, 0xf8, 0x00, 0x00, 0x7c, 0xc0, 0x01, 0x07, 0x3e, 0x00, 0x00, 0xf0, 0x81, 0x03, 0x0e, 0x0f, 
	0x00, 0x00, 0xc0, 0xc3, 0x01, 0x9c, 0x03, 0xf0, 0x3f, 0x00, 0xe7, 0x00, 0xf8, 0x01, 0xfe, 0xff, 
	0x01, 0x7e, 0x00, 0xf0, 0x80, 0x1f, 0xe0, 0x07, 0x3c, 0x00, 0x20, 0xe0, 0x01, 0x00, 0x1e, 0x10, 
	0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 
	0x0e, 0xe0, 0x1f, 0xc0, 0x01, 0x00, 0x00, 0x0e, 0xfc, 0xff, 0xc0, 0x01, 0x00, 0x00, 0x1c, 0x1f, 
	0xe0, 0xe3, 0x00, 0x00, 0x00, 0x98, 0x07, 0x80, 0x77, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0x3e, 
	0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x20, 0xc0, 0x0f, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0xf8, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0e, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x38, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xe0, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//display_rollingHome
u8g2_uint_t offset;			// current offset for the scrolling text
u8g2_uint_t width;			// pixel width of the scrolling text (must be lesser than 128 unless U8G2_16BIT is defined
const char *text = "Rollin' Back Home                    ";	// scroll this text from right to left
static const unsigned char image_FaceCharging_29x14_bits[] U8X8_PROGMEM = {0x40,0x00,0x00,0x02,0x60,0x00,0x00,0x03,0x30,0x00,0x80,0x01,0x18,0x00,0xc0,0x00,0xfc,0x00,0xe0,0x07,0xfc,0x00,0xe0,0x07,0x60,0x00,0x00,0x03,0x30,0x00,0x80,0x01,0x18,0x00,0xc0,0x00,0x08,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x08,0x02,0x00,0x00,0xf0,0x01,0x00};
u8g2_uint_t x;
#define BUZZER_PIN 22
#define TRIG_PIN A6
#define ECHO_PIN A7
#define DEBUG true
#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor2  L298 Pin in2 
#define in3 7 //Motor3  L298 Pin in3 
#define in4 6 //Motor4  L298 Pin in4 
#define enB 11//Enable2 L298 Pin enB 
int speed = 100;
const int DISTANCE_THRESHOLD = 20; // centimeters
short int duration_us, distance_cm;
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
char lastColor;//EEPROM value
int address = 0;//EEPROM Address
String ipAddress;

void setup()
{
  Serial.begin(9600); //Serial communication
  Serial1.begin(9600);//for communication with esp
  u8g2.begin();//oled start
  u8g2.setBitmapMode(1);//transparent mode
  u8g2.setFontMode(1); //transparent mode
  //MOTOR PINS
  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
  pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 
  //COLOR Sensor 
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);//set frequency 100%
  pinMode(s2L, OUTPUT);
  pinMode(s3L, OUTPUT);
  pinMode(outL, INPUT);//left color
  pinMode(s2R, OUTPUT);
  pinMode(s3R, OUTPUT);
  pinMode(outR, INPUT);//right color
  pinMode(TRIG_PIN, OUTPUT);    
  pinMode(ECHO_PIN, INPUT); //ultrasonic 
  pinMode(BUZZER_PIN, OUTPUT);//buzzer
  lastColor = EEPROM.read(address);   
  display_intro();
  display_last_path(lastColor);
  display_WiFi_connect();
  WiFi_initialize();
  display_ip();
  while(!Serial1.available());
  receiveInfo();
}

void loop()
{
  if(color == "red" || color == "green" || color == "blue")
  {
    LeaveHome();
    colorToReturn = color;
    while(color != "yellow"){
      ultrasonic_read();
      if(distance_cm > DISTANCE_THRESHOLD){
        digitalWrite(BUZZER_PIN, LOW);
        display_status(color);
        ColorDetect();
        executeColor(color);
        FoundYellow();
        Direction();
      }
      else{
        stop();
        digitalWrite(BUZZER_PIN, HIGH);
      }
    }
  }
  else
  {
    //Serial.print("ColorToReturn: ");Serial.print(colorToReturn);
    updateEEPROM(colorToReturn);
    while(color == "yellow"){ReturnHome(colorToReturn);}
  }
  lastColor = EEPROM.read(address);         
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------WI-FI------------------------------------------------------------//
//**********FUNCTION TO CHECK WHETHER ESP IS RECEVING INFOMATION OR NOT*******//
void receiveInfo()
{
  if(Serial1.available()) // check if the esp is sending a message
  {
    if(Serial1.find("+IPD,"))
    {
      delay(1000);// wait for the serial buffer to fill up (read all the serial data)
      int connectionId = Serial1.read() - '0';// get the connection id so that we can then disconnect
      Serial1.find("color=");
      // Read until either a space or carriage return is encountered
      color = Serial1.readStringUntil(' ');
      Serial1.readStringUntil('\n');

      /*Serial.print("Received color: ");
      Serial.println(color);*/

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
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)*/
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";    
  Serial1.print(command); // send the read character to the esp8266   
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

//****************************FUNCTION TO INITIALIZE WIFI***************************//
void WiFi_initialize()
{
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point and stationary
  sendData("AT+CWJAP=\"AustonMMCampus\",\"helloyangon\"\r\n",5000,DEBUG); //connect wifi
  //sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  ipAddress = getIPaddress();
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}

//-------------------------------------------------------------------------------------------------------------------------------------------//

//--------------------------------------------------------CONTROL MECHANISM------------------------------------------------------------------//
//*******************FUNCTION TO RETURN HOME******************//
void ReturnHome(String colorToReturn)
{
  while(sensor_left == 0 || sensor_right == 0)
  {
    ColorDetect();
    executeColor(colorToReturn);
    turnRight();delay(100);
  }
  while(color == "yellow")
  {
    ultrasonic_read();
    if(distance_cm > DISTANCE_THRESHOLD)
    {
      digitalWrite(BUZZER_PIN, LOW);
      display_rollingHome();
      ColorDetect();
      executeColor(colorToReturn);
      FoundYellowHome();Direction();
    }
    else{stop();digitalWrite(BUZZER_PIN, HIGH);}
  }
}

//*****************FUNCTION TO LEAVE HOME*******************//
void LeaveHome()
{
  if(color == "red" && lastColor == 'r'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnRight();/*delay(50);*/}forward();delay(300);}
  else if(color == "red" && lastColor == 'g'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnLeft();/*delay(50);*/}forward();delay(300);}
  else if(color == "red" && lastColor == 'b'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Red();turnRight();/*delay(50);*/}forward();delay(300);}
  else if(color == "green" && lastColor == 'r'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Green();turnRight();/*delay(50);*/}forward();delay(300);}
  else if(color == "green" && lastColor == 'g'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Green();turnLeft();/*delay(50);*/}forward();delay(300);}
  else if(color == "green" && lastColor == 'b'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Green();forward();/*delay(50);*/}forward();delay(300);}
  else if(color == "blue" && lastColor == 'r'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Blue();turnLeft();/*delay(50);*/}forward();delay(300);}
  else if(color == "blue" && lastColor == 'g'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Blue();forward();/*delay(50);*/}forward();delay(300);}
  else if(color == "blue" && lastColor == 'b'){while(sensor_left == 0 || sensor_right == 0){ColorDetect();Blue();turnRight();/*delay(50);*/}forward();delay(300);}
}

//*******************FUNCTION TO EXECUTE ACCORDING TO COLOR********************//
void executeColor(String currentColor)
{
  if(currentColor == "red")Red();
  else if(currentColor == "green")Green();
  else if(currentColor == "blue")Blue();
}

//********************FUNCTION TO UPDATE EEPROM*************************//
void updateEEPROM(String latestColor)
{
  if(latestColor == "red"){EEPROM.update(address, 'r');}
  else if(latestColor == "green"){EEPROM.update(address, 'g');}
  else{EEPROM.update(address, 'b');}
}

//***********YELLOW FOUND?************//
void FoundYellow()
{
  Yellow();
  if(yellow_left == 1 && yellow_right == 1 && sensor_left == 0 && sensor_right == 0)
  {
    forward();delay(200);
    //Serial.println("Reached yellow!STOPPED");
    while(color != "yellow"){display_whenReach();stop();receiveInfo();}
  }
}

void FoundYellowHome()
{
  Yellow();
  if(yellow_left == 1 && yellow_right == 1 && sensor_left == 0 && sensor_right == 0)
  {
    if(colorToReturn == "red"){forward();delay(300);}
    else{forward();delay(400);}
    //Serial.println("Reached HOME!STOPPED");
    while(color == "yellow"){display_whenReach();stop();receiveInfo();}
  }
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

//***********************FUNCTION TO DETECT COLOR[RED/GREEN/BLUE/YELLOW]***************************//
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
  if (blueL <= 15 && redL >= 22 && greenL >= 16 && blueL < redL && blueL < greenL)
  {sensor_left = 1;}
  else
  {sensor_left = 0;}

  //Sensor Right
  if (blueR <= 23 && redR >= 24 && greenR >= 25 && blueR < redR && blueR < greenR)
  {sensor_right = 1;}
  else
  {sensor_right = 0;}
}

void Yellow()
{
  //if(redL >= 6 && redL <= 15 && greenL >=  && greenL <=  && blueL >=  && blueL <= )
  if(redL <= 7 && greenL >= 8 && blueL >= 10 && redL < greenL && redL < blueL)
  {yellow_left = 1;}
  else
  {yellow_left = 0;}
  //if(redR >=  && redR <=  && greenR >=  && greenR <=  && blueR >=  && blueR <= )
  if(redR <= 7 && greenR >= 9 && blueR >= 12 && redR < greenR && redR < blueR)
  {yellow_right = 1;}
  else
  {yellow_right = 0;}
}

//***************FUNCTION TO CONTROL DIRECTION*******************//
void Direction()
{ //Direction 
  if (sensor_left == 1 && sensor_right == 1)
  {//forward
    forward();
    //delay(50);
    //stop();
    //Serial.println("Going forward ");
  }
  else if (sensor_left == 0 && sensor_right == 1)
  {//Right Curve
    turnRight();
    //delay(50);
    //stop();
    //Serial.println("Turning Right");
  }
  else if (sensor_left == 1 && sensor_right == 0)
  {//Left Curve
    turnLeft();
    //delay(50);
    //stop();
    //Serial.println("Turning Left"); 
  } 
  else
  {
    stop();
    delay(200);
    backward();
    //delay(100);
    //stop();
    //Serial.println("Color detection ERROR!NO LINE DETECTED");  
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

//---------------------------------------------------------------------------------------------------------------------------//
//----------------------------------------------------ULTRASONIC AND BUZZER--------------------------------------------------//
//**************************FUNCTION TO READ DISTANCE**********************//
void ultrasonic_read()
{
  duration_us = 0;distance_cm = 0;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN,HIGH);
  distance_cm = 0.017 * duration_us;
}

//*******************************FUNCTION TO PLAY ALARM SOUND********************************//

//----------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------OLED DISPLAY----------------------------------------------------//
//**************************FUNCTION TO DISPLAY INTRO***************************//
void display_intro()
{
  static const unsigned char image_Layer_27_bits[] U8X8_PROGMEM = {0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x03,0x00,0x06,0x00,0x0c,0x00,0x18,0x00,0x10,0x00,0x70,0x00,0xc0,0x03,0x00,0x06};
  static const unsigned char image_Layer_28_bits[] U8X8_PROGMEM = {0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x06,0x00,0x03,0x80,0x01,0xc0,0x00,0x40,0x00,0x70,0x00,0x1c,0x00,0x06,0x00,0x03,0x00};
  u8g2.firstPage();
  do {
    //u8g2.setBitmapMode(1);
    //u8g2.setFontMode(1);
    u8g2.setFont(u8g2_font_lubR14_te);//u8g2_font_profont22_tr);
    u8g2.drawStr(13, 37, "Auston");
    u8g2.drawFrame(91, 11, 2, 24);
    u8g2.drawFrame(92, 36, 26, 2);
    u8g2.drawLine(94, 11, 117, 34);
    u8g2.drawLine(95, 11, 118, 34);
    u8g2.drawLine(95, 16, 95, 32);
    u8g2.drawLine(96, 32, 96, 17);
    u8g2.drawLine(97, 32, 97, 18);
    u8g2.drawLine(98, 32, 98, 19);
    u8g2.drawLine(99, 32, 99, 20);
    u8g2.drawLine(100, 32, 100, 21);
    u8g2.drawLine(101, 32, 101, 22);
    u8g2.drawLine(103, 32, 103, 24);
    u8g2.drawLine(102, 32, 102, 23);
    u8g2.drawLine(105, 32, 105, 26);
    u8g2.drawLine(104, 32, 104, 25);
    u8g2.drawLine(107, 32, 107, 28);
    u8g2.drawLine(106, 32, 106, 27);
    u8g2.drawLine(108, 32, 108, 29);
    u8g2.drawLine(109, 32, 109, 30);
    u8g2.drawLine(110, 32, 110, 31);
    u8g2.drawPixel(111, 32);
  } while ( u8g2.nextPage() );
  delay(5000);

  u8g2.firstPage();
  do {
    //u8g2.setBitmapMode(1);
    //u8g2.setFontMode(1);
    u8g2.drawFrame(37, 13, 2, 24);
    u8g2.drawFrame(38, 38, 26, 2);
    u8g2.drawLine(40, 13, 63, 36);
    u8g2.drawLine(41, 13, 64, 36);
    u8g2.drawLine(41, 18, 41, 34);
    u8g2.drawLine(42, 34, 42, 19);
    u8g2.drawLine(43, 34, 43, 20);
    u8g2.drawLine(44, 34, 44, 21);
    u8g2.drawLine(45, 34, 45, 22);
    u8g2.drawLine(46, 34, 46, 23);
    u8g2.drawLine(47, 34, 47, 24);
    u8g2.drawLine(49, 34, 49, 26);
    u8g2.drawLine(48, 34, 48, 25);
    u8g2.drawLine(51, 34, 51, 28);
    u8g2.drawLine(50, 34, 50, 27);
    u8g2.drawLine(53, 34, 53, 30);
    u8g2.drawLine(52, 34, 52, 29);
    u8g2.drawLine(54, 34, 54, 31);
    u8g2.drawLine(55, 34, 55, 32);
    u8g2.drawLine(56, 34, 56, 33);
    u8g2.drawPixel(46, 29);
    u8g2.drawFrame(71, 14, 20, 9);
    u8g2.drawBox(76, 17, 2, 2);
    u8g2.drawBox(84, 17, 2, 2);
    u8g2.drawBox(80, 12, 2, 2);
    u8g2.drawLine(70, 26, 91, 26);
    u8g2.drawXBMP( 70, 27, 11, 13, image_Layer_27_bits);
    u8g2.drawXBMP( 81, 26, 11, 14, image_Layer_28_bits);
    u8g2.setFont(u8g2_font_press_mel_tr);//(u8g2_font_cube_mel_tr);
    u8g2.drawStr(48, 56, "A-bot");
  } while ( u8g2.nextPage() );
  delay(5000);
}

//*******************************FUNCTION TO DISPLAY WIFI ANIMATE***************************//
void display_WiFi_connect()
{
  u8g2.firstPage();
  do {          //xpos,ypos,width,heigh,bitmap
    u8g2.drawXBMP(39,0,50,50,epd_bitmap_wifi);
    u8g2.setFont(u8g2_font_6x13_te);
    u8g2.drawStr(30,62,"Connecting...");
  } while ( u8g2.nextPage() );
}

//****************************FUNCTION TO DISPLAY IP ADDRESS**********************************//
void display_ip()
{
  u8g2.firstPage();
  do {
    //u8g2.setBitmapMode(1);
    //u8g2.setFontMode(1);
    u8g2.setFont(u8g2_font_DigitalDisco_tf);
    u8g2.drawStr(4, 16, "Wi-Fi Connected!");
    u8g2.drawLine(0,23,128,23);
    u8g2.drawLine(10,25,118,25);
    u8g2.setFont(u8g2_font_tenthinguys_tf);//u8g2_font_t0_22b_me);//u8g2_font_tenthinguys_tf);
    u8g2.drawStr(0, 49, "IP- ");
    u8g2.setFont(u8g2_font_helvB14_tn);//u8g2_font_DigitalDisco_tn);
    u8g2.setCursor(22, 49);
    u8g2.print(ipAddress);
  } while ( u8g2.nextPage() );
}

//**************************FUNCTION TO DISPLAY A BOT STATUS*********************//
void display_status(String status)
{
  static const unsigned char image_ButtonRight_4x7_bits[] U8X8_PROGMEM = {0x01,0x03,0x07,0x0f,0x07,0x03,0x01};
  static const unsigned char image_ButtonLeft_4x7_bits[] U8X8_PROGMEM = {0x08,0x0c,0x0e,0x0f,0x0e,0x0c,0x08};
  //classroom 1
  if(status == "red")
  {
    u8g2.firstPage();
    do{
      u8g2.setFont( u8g2_font_HelvetiPixelOutline_tr);
      u8g2.drawStr(15, 45, "Classroom-1");
      u8g2.setFont(u8g2_font_sticker100complete_tr);//u8g2_font_greenbloodserif2_tr);//u8g2_font_cupcakemetoyourleader_tr);//u8g2_font_jinxedwizards_tr);
      u8g2.drawStr(20, 19, "Duty Call!");
      u8g2.drawXBMP(5, 37, 4, 7, image_ButtonRight_4x7_bits);
      u8g2.drawXBMP( 120, 37, 4, 7, image_ButtonLeft_4x7_bits);
    } while ( u8g2.nextPage() );
  }
  //classroom 2
  else if(status == "green")
  {
    u8g2.firstPage();
    do{
      u8g2.setFont( u8g2_font_jinxedwizards_tr);
      u8g2.drawStr(20, 45, "Classroom-2");
      u8g2.setFont(u8g2_font_moosenooks_tr);//u8g2_font_greenbloodserif2_tr);//u8g2_font_cupcakemetoyourleader_tr);//u8g2_font_jinxedwizards_tr);
      u8g2.drawStr(25, 19, "Duty Call!");
      u8g2.drawXBMP(5, 37, 4, 7, image_ButtonRight_4x7_bits);
      u8g2.drawXBMP( 120, 37, 4, 7, image_ButtonLeft_4x7_bits);
    } while ( u8g2.nextPage() );
  }
  //labroom
  else 
  {
    u8g2.firstPage();
    do{
      u8g2.setFont(u8g2_font_cube_mel_tr);
      u8g2.drawStr(30, 45, "Labroom");
      u8g2.setFont(u8g2_font_press_mel_tr);
      u8g2.drawStr(28, 19, "Duty Call!");
      u8g2.drawXBMP(15, 37, 4, 7, image_ButtonRight_4x7_bits);
      u8g2.drawXBMP( 110, 37, 4, 7, image_ButtonLeft_4x7_bits);
    }while ( u8g2.nextPage() );
  }
}

//************************************FUNCTION TO DISPLAY ROLLING HOME******************************//
void display_rollingHome()
{
   u8g2.setFontMode(0);		// enable transparent mode, which is faster
   u8g2.setFont(u8g2_font_tenthinnerguys_t_all);	// set the target font to calculate the pixel width
   width = u8g2.getUTF8Width(text);		// calculate the pixel width of the text
   u8g2.firstPage();
   do {
    // draw the scrolling text at current offset
    x = offset;
    u8g2.setFont(u8g2_font_tenthinnerguys_t_all);		// set the target font
    do {								// repeated drawing of the scrolling text...
      u8g2.drawUTF8(x, 13, text);			// draw the scolling text
      x += width;						// add the pixel width of the scrolling text
    } while( x < u8g2.getDisplayWidth() );		// draw again until the complete display is filled
    u8g2.setFont(u8g2_font_prospero_bold_nbp_tf );
    u8g2.drawStr(15, 56, "Home Sweet Home");
    u8g2.drawPixel(4, 47);
    u8g2.drawPixel(6, 49);
    u8g2.drawPixel(4, 55);
    u8g2.drawPixel(5, 48);
    u8g2.drawPixel(3, 54);
    u8g2.drawPixel(1, 51);
    u8g2.drawPixel(1, 52);
    u8g2.drawPixel(1, 50);
    u8g2.drawPixel(2, 49);
    u8g2.drawPixel(3, 48);
    u8g2.drawPixel(2, 53);
    u8g2.drawPixel(7, 50);
    u8g2.drawPixel(11, 48);
    u8g2.drawPixel(9, 48);
    u8g2.drawPixel(8, 49);
    u8g2.drawPixel(10, 47);
    u8g2.drawPixel(13, 51);
    u8g2.drawPixel(13, 52);
    u8g2.drawPixel(13, 50);
    u8g2.drawPixel(12, 49);
    u8g2.drawPixel(12, 53);
    u8g2.drawPixel(7, 58);
    u8g2.drawPixel(6, 57);
    u8g2.drawPixel(5, 56);
    u8g2.drawPixel(9, 56);
    u8g2.drawPixel(10, 55);
    u8g2.drawPixel(11, 54);
    u8g2.drawPixel(8, 57);
    u8g2.drawPixel(114, 50);
    u8g2.drawPixel(114, 51);
    u8g2.drawPixel(114, 52);
    u8g2.drawPixel(115, 53);
    u8g2.drawPixel(116, 54);
    u8g2.drawPixel(117, 55);
    u8g2.drawPixel(118, 56);
    u8g2.drawPixel(119, 57);
    u8g2.drawPixel(120, 58);
    u8g2.drawPixel(121, 57);
    u8g2.drawPixel(122, 56);
    u8g2.drawPixel(123, 55);
    u8g2.drawPixel(124, 54);
    u8g2.drawPixel(125, 53);
    u8g2.drawPixel(126, 52);
    u8g2.drawPixel(126, 51);
    u8g2.drawPixel(126, 50);
    u8g2.drawPixel(119, 49);
    u8g2.drawPixel(120, 50);
    u8g2.drawPixel(121, 49);
    u8g2.drawPixel(122, 48);
    u8g2.drawPixel(123, 47);
    u8g2.drawPixel(124, 48);
    u8g2.drawPixel(125, 49);
    u8g2.drawPixel(116, 48);
    u8g2.drawPixel(117, 47);
    u8g2.drawPixel(118, 48);
    u8g2.drawPixel(115, 49);
    u8g2.drawXBMP( 45, 25, 29, 14, image_FaceCharging_29x14_bits);   
  } while ( u8g2.nextPage() );
  
  offset-=5;							// scroll by one pixel
  if ( (u8g2_uint_t)offset < (u8g2_uint_t)-width )	
    offset = 0;							// start over again
    
  //delay(10);							// do some small delay
}

//****************************************FUNCTION TO DISPLAY WHEN REACHED**********************************************//
void display_whenReach()
{
  static const unsigned char image__587389d8f3a71010b5e8ef4b12323_bits[] U8X8_PROGMEM = {0x00,0x00,0x00,0x00,0xc0,0x01,0xf0,0x00,0xc0,0x03,0xf0,0x00,0xc0,0x01,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x08,0x07,0x00,0x00,0x38,0x07,0x00,0x00,0x18,0x06,0x00,0x00,0x1c,0x0e,0x00,0x00,0x1c,0x0e,0x00,0x00,0x0e,0x1c,0x00,0x00,0x0e,0x3c,0x00,0x00,0x07,0x38,0x00,0x80,0x07,0xf0,0x00,0xc0,0x03,0xe0,0x01,0xf0,0x01,0xc0,0x0f,0xfc,0x00,0x80,0xff,0x3f,0x00,0x00,0xfc,0x0f,0x00,0x00,0xe0,0x01,0x00};
  u8g2.firstPage();
  do {
   //u8g2.setFontMode(1);  /* activate transparent font mode */
   u8g2.setDrawColor(1); /* color 1 for the box */
   u8g2.drawBox(15, 2, 35, 50);
   u8g2.setFont(u8g2_font_ncenB14_tf);
   u8g2.setDrawColor(2);
   u8g2.drawStr(36, 18, "A bot");
   u8g2.setFont(u8g2_font_6x10_tr);
   u8g2.drawStr(20, 32, "At your service");
   u8g2.drawXBMP( 50, 37, 30, 23, image__587389d8f3a71010b5e8ef4b12323_bits);
  } while ( u8g2.nextPage() );
}

//**********************FUNCTION TO DISPLAY LAST PATH****************************//
void display_last_path(char path)
{
  String last_path;
  if(path = 'r'){last_path = "red";}
  else if(path = 'g'){last_path = "green";}
  else{last_path = "blue";}
  u8g2.firstPage();
  do{
    u8g2.setFont(u8g2_font_helvB14_tn);
    u8g2.drawStr(28, 19, "Last Path-");
    u8g2.setCursor(36, 49);
    u8g2.print(last_path);
  } while (u8g2.nextPage());
  delay(3000);
}
