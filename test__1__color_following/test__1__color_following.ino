#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 11//Enable2 L298 Pin enB 
const int speed = 150;
//Color Sensor
const int s0 = 4; //Conection for Sensor
const int s1 = 5;
//for left
const int s2L = A4;
const int s3L = A5;
const int outL = A3;

int redL = 0; //Left color sensor
int greenL = 0;
int blueL = 0;
//for right
const int s2R = A1;
const int s3R = A2;
const int outR = A0;

int redR = 0; //Right color sensor
int greenR = 0;
int blueR = 0;

int sensor_left = 0;
int sensor_right = 0;

int yellow_left = 0;
int yellow_right = 0;

void setup()
{
  Serial.begin(9600); //Serial communication
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
}

void loop()
{
  color();
  Serial.print("LEft_");
  Serial.print(redL);
  Serial.print(",");
  Serial.print(greenL);
  Serial.print(",");
  Serial.print(blueL);
  Serial.print(",");
  Serial.print("Right_");
  Serial.print(redR);
  Serial.print(",");
  Serial.print(greenR);
  Serial.print(",");
  Serial.print(blueR);
  delay(300);

  { //detection
  //Red();
  //Green();
  //Yellow();
  Blue();
  }
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
   else
    {
      stop();
      delay(500);
      backward();
      delay(100);
      stop();
      Serial.println("Color detection ERROR!NO LINE DETECTED");   
    }
    //if(yellow_left ==1 && yellow_right ==1){stop();Serial.println("YELLOW");}
    /*else if (yellow_left == 1 && yellow_right ==1 && sensor_left == 0 && sensor_right == 0)
    {
      stop();
      delay(500);
      forward();
      delay(250);
      turnLeft();
      delay(900);
      stop();
      delay(500);
      turnRight();
      delay(100);
      //forward();
      //delay(100);
      Red();
      if(sensor_left == 1 && sensor_right == 0){turnLeft();delay(50);stop();}
      else if(sensor_left == 0 && sensor_right == 1){turnRight();delay(50);stop();}
      else if(sensor_left == 1 && sensor_right == 1)
      {
      backward();
      delay(500);
      Serial.print("Home");
      while(yellow_left ==1 && yellow_right ==1){stop();}
    }*/
  }
}

//Read color values
void color() 
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
{
  //Sensor Left
  //if (redL <= 15 && greenL >= 15 && blueL >= 15 && redL < blueL && redL < greenL)
  if(redL >= 5 && redL <= 15 && greenL >= 10 && greenL <= 25 && blueL >= 10 && blueL <= 25)
  {
    sensor_left = 1;
  }
  else
  {
    sensor_left = 0;
  }

  //Sensor Right
  //if (redR <= 15 && greenR >= 15 && blueR >= 15 && redR < blueR && redR < greenR)
  if(redR >= 5 && redR <= 15 && greenR >= 10 && greenR <= 30 && blueR >= 10 && blueR <= 25)
  {
    sensor_right = 1;
  }
  else
  {
    sensor_right = 0;
  }
}
void Green()
{
  { //Sensor Left
    if (greenL <= 15 && greenL >= 5 && redL <=20 && redL >=7 && blueL <= 20 && blueL >= 7)
    //if(greenL <= 15 && redL >= 12 && blueL >= 6 && greenL<redL)
    {
      sensor_left = 1;
    }
    else
    {
      sensor_left = 0;
    }
  }

  { //Sensor Right
    if (greenR <= 15 && greenR >= 5 && redR<= 25 && redR >= 10 && blueR <= 23 && blueR >= 10)
    //if(greenR <= 23 && redR >= 14 && blueR >= 13 && greenR < redR)
    {
      sensor_right = 1;
    }
    else
    {
      sensor_right = 0;
    }
  }
}
void Blue()
{
  { //Sensor Left
    if (redL >= 10 && redL <= 45 && greenL >= 10 && greenL <= 35 && blueL >= 5 && blueL <= 20)
    //if (blueL <= 15 && redL >= 15 && greenL >= 15 && blueL < redL && blueL < greenL)
    {
      sensor_left = 1;
    }
    else
    {
      sensor_left = 0;
    }
  }

  { //Sensor Right
    if (redR >= 10 && redR <= 45 && greenR >= 10 && greenR <= 35 && blueR >= 5 && blueR <= 20)
    //if (blueR <= 15 && redR >= 15 && greenR >= 15 && blueR < redR && blueR < greenR)
    {
      sensor_right = 1;
    }
    else
    {
      sensor_right = 0;
    }
  }
}
/*void Yellow()
{
  if(redL >= 5 && redL <= 10 && greenL >= 5 && greenL <= 10 && blueL >= 7 && blueL <= 10)
  //if(redL <= 9 && greenL >= 8 && blueL >= 8 && redL < greenL && redL < blueL)
  {yellow_left = 1;}
  else{yellow_left = 0;}
  if(redR >= 5 && redR <= 10 && greenR >= 5 && greenR <= 10 && blueR >= 10 && blueR <= 12)
  //if(redR <= 15 && greenR >= 8 && blueR >= 10 && redR < greenR && redR < blueR)
  {yellow_right = 1;}
  else{yellow_right = 0;}
}*/
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
