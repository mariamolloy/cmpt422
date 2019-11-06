/*
  Maria Molloy Lab 4

  Despacito Song Code by msr048 from
  https://create.arduino.cc/projecthub/msr048/despacito-melody-9dcab7?f=1

*/


#include "pitches.h"
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int noteDuration;
int pauseBetweenNotes = 0;
int tempo;

const int switchPin = 8;
unsigned long previousTime = 0;
int switchState = 0;
int prevSwitchState = 0;
int led = 2; //pin number
long interval = 3000;

#include <Servo.h>

Servo myServo;


void setup() {
  for (int i = 2; i < 6; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(switchPin, INPUT);
  pinMode(13, OUTPUT);

  myServo.attach(9);

  tempo = 640;
}

void loop() {

  unsigned long currentTime = millis();

  if (currentTime - previousTime > interval) {
    previousTime = currentTime;
    digitalWrite(led, HIGH);
    led++;
    if (led == 6) {

      delay(3000);
      chorus();

      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);

      delay(1000);
      myServo.write(170);
      delay(1000);
      myServo.write(100);
      delay(1000);
      myServo.write(170);
      delay(1000);
      myServo.write(100);
      delay(1000);

    }
  }

  switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState) {
    for (int i = 2; i < 6; i++) {
      digitalWrite(i, LOW);
    }
    led = 2;
    previousTime = currentTime;
  }
  prevSwitchState = switchState;

}

void chorus() {
  note(tempo, NOTE_D5);
  note(tempo, NOTE_CS5);
  digitalWrite(led1, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);// (1)
  digitalWrite(led4, LOW);
  note(tempo / 2, NOTE_B4);
  note(tempo / 4, NOTE_FS4);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH);// (2)
  digitalWrite(led4, HIGH);
  delay(tempo / 4);
  digitalWrite(led3, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);// (3)
  note(tempo / 4, NOTE_FS4);
  note(tempo / 4, NOTE_FS4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);// (4)
  note(tempo / 4, NOTE_FS4);
  note(tempo / 4, NOTE_FS4);
  digitalWrite(led1, HIGH);   //  (1)
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  note(tempo / 4, NOTE_FS4);

  note(tempo / 4, NOTE_B4);
  note(tempo / 4, NOTE_B4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);//  (2)
  note(tempo / 4, NOTE_B4);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);//  (3)
  note(tempo / 2, NOTE_B4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);//  (4)

  note(tempo / 4, NOTE_A4);

  note(tempo / 4, NOTE_B4);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);//  (1)
  delay(tempo / 4);
  delay(tempo / 4);
  note(tempo / 4, NOTE_G4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);//  (2)
  delay(tempo / 4);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);//  (3)
  //......
  note(tempo / 4, NOTE_G4);
  note(tempo / 4, NOTE_G4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);//  (4)
  note(tempo / 4, NOTE_G4);
  note(tempo / 4, NOTE_G4);
  digitalWrite(led2, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);//  (1)
  note(tempo / 4, NOTE_G4);

  note(tempo / 4, NOTE_B4);
  note(tempo / 4, NOTE_B4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);//  (2)
  note(tempo / 4, NOTE_B4);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);//  (3)
  note(tempo / 2, NOTE_B4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);//  (4)

  note(tempo / 4, NOTE_CS5);
  note(tempo / 4, NOTE_D5);
  digitalWrite(led1, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);//  (1)
  delay(tempo / 4);
  delay(tempo / 4);
  note(tempo / 4, NOTE_A4);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led4, HIGH);//  (2)
  delay(tempo / 4);
  digitalWrite(led1, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led4, LOW);//  (3)

  note(tempo / 4, NOTE_A4);
  note(tempo / 4, NOTE_A4);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led4, LOW);//  (4)
  note(tempo / 4, NOTE_A4);
  note(tempo / 4, NOTE_A4);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);//  (1)

  note(tempo / 4, NOTE_D5);
  note(tempo / 4, NOTE_CS5);
  note(tempo / 4, NOTE_D5);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);//  (2)
  note(tempo / 4, NOTE_CS5);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);//  (3)
  note(tempo / 2, NOTE_D5);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);//  (4)
  //
  note(tempo / 4, NOTE_E5);
  note_jai(tempo / 2, NOTE_E5, tempo / 4); // (1)
  //     note(tempo/2, NOTE_E5);

  //-----------------------------------------------
  tone(13, NOTE_CS5, tempo * 3 / 4);
  //-----------------------------------------------
  delay(tempo / 4);
  delay(tempo / 4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);//  (2)
  delay(tempo / 4);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);//  (3)
  noTone(13);
  delay(tempo / 4);

  //--------------
  delay(tempo / 4);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);//  (4)

  delay(tempo / 4);
  delay(tempo / 4);

}
void note(int noteDuration, int notex ) {

  //noteDuration=tempo/4;
  tone(13, notex, noteDuration * 0.9);
  //      pauseBetweenNotes = noteDuration * 1.30;
  pauseBetweenNotes = noteDuration * 1.1;
  delay(pauseBetweenNotes);
  noTone(13);


}
void note_jai(int noteDuration, int notex, int rest) {

  //noteDuration=tempo/4;
  tone(13, notex, noteDuration * 0.9);
  //      pauseBetweenNotes = noteDuration * 1.30;
  pauseBetweenNotes = noteDuration * 1.1;
  delay(rest);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);//  (1)

  delay(pauseBetweenNotes - rest);
  noTone(13);


}