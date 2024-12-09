#include "pitches.h"
#define BUZZER_PIN 8

//Perfect
int melody[] = 
{
NOTE_A4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_A4,//2
NOTE_G4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4,
NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4,
NOTE_D4, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_A4
};

int durations[] =
 {8,4,4,4,
  8,8,8,4,4,4,
  8,8,8,4,8,8,
  8,4,4,4,8,8,4
};

int melody1[] = 
{
NOTE_B4, NOTE_G5, NOTE_FS5, NOTE_E5,
NOTE_CS5, NOTE_A4, NOTE_CS5, NOTE_E5, NOTE_FS5, NOTE_A4, NOTE_FS5,
NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_CS5, NOTE_A4, NOTE_CS5, NOTE_A5, NOTE_FS5
};

int durations1[] =
 {8,
  8,8,8,8,4,8,4,8,8,8,8,8,8,4,4,4,4,8,8,8,8,6,4,4,8,2
};

int melody2[] = { NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
NOTE_G3, NOTE_D4, NOTE_G4, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5,
NOTE_C5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4};

int durations2[] = { 8,8,8,8,8,8,8,4,
8,8,8,8,8,8,8,4,
4,4,4,4,4,4,8,8,4};

int melody3[] = {
  NOTE_G4, NOTE_C5, NOTE_C5, NOTE_C5, 
  NOTE_G4, NOTE_D5, NOTE_D5, NOTE_D5, 
  NOTE_A4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_C5,0,
  NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, 
};

  int durations3[] = {
//  8,8,8,8,4,4,2,
 // 8,8,2,4,2,
  8,4,8,2,
  8,4,8,2, 
  8,4,8,4,4,2,0,
  8,4,8,2,
  8,4,4,8,4,4,2,
  8,4,8,3,
  8,4,8,3,
  8,4,8,4,4,3,
  8,4,8,3,8,4,8,4,8,4,3,
  8,8,4,3,4,
  4,4,4,
  4,4,4,4,8,4,3,
  4,8,4,8,4,8,4,4,2,
  4,4,4,8,4,4,3,8,
  4,4,4,8,4,4,3,
  4,4,4,8,3,
  8,4,8,4,8,2,2,2
  //my love
  };

void setup() {
    Serial.begin(9600);              
    pinMode(BUZZER_PIN, OUTPUT);  
  for (int i = 0; i < sizeof(melody3) / sizeof(melody3[0]); i++) {
          play_myLove(melody3[i], durations3[i]);
        }
}
void play_perfect(int note, int duration) {
    int noteDuration = 2000/ duration;
    tone(BUZZER_PIN, note, noteDuration);
    delay(noteDuration + 50);
    noTone(BUZZER_PIN);
    delay(50);
}

void play_cupid(int note, int duration) {
    int noteDuration = 2000/ duration;
    tone(BUZZER_PIN, note, noteDuration);
    delay(noteDuration + 50);
    noTone(BUZZER_PIN);
    delay(50);
}

void play_waiting4u(int note, int duration) {
    int noteDuration = 2000/ duration;
    tone(BUZZER_PIN, note, noteDuration);
    delay(noteDuration + 50);
    noTone(BUZZER_PIN);
    delay(50);
}
void play_myLove(int note, int duration) {
    int noteDuration1 = 2000/ duration;
    tone(BUZZER_PIN, note, noteDuration1);
    delay(noteDuration1 + 50);
    noTone(BUZZER_PIN);
    delay(50);

}
void loop() {  
        
}