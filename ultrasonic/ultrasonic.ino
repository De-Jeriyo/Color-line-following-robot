const int triggerPin = 2;  // Connect Trigger pin of the ultrasonic sensor to digital pin 2
const int echoPin = 3;     // Connect Echo pin of the ultrasonic sensor to digital pin 3

volatile unsigned long pulseWidth = 0;  // Variable to store the pulse width
volatile unsigned long distance = 0;    // Variable to store the calculated distance

void setup() {
  Serial.begin(9600);
  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(echoPin), measureDistance, CHANGE);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);  // Delay for one second before the next measurement
}

void measureDistance() {
  if (digitalRead(echoPin) == HIGH) {
    // Start measuring the pulse width when the echo pin goes high
    pulseWidth = micros();
  } else {
    // Calculate the distance when the echo pin goes low
    pulseWidth = micros() - pulseWidth;
    distance = pulseWidth / 58;  // Convert pulse width to distance in centimeters
  }
}
