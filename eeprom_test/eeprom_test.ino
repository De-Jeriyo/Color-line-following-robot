#include <EEPROM.h>
int address = 0;
char lastColor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lastColor = EEPROM.read(address);
  Serial.print(lastColor);
  /*EEPROM.update(address,'r');
  lastColor = EEPROM.read(address);
  Serial.print(lastColor);*/
  EEPROM.update(address,'b');
  lastColor = EEPROM.read(address);
  Serial.print(lastColor);
}

void loop() {
  // put your main code here, to run repeatedly:

}
