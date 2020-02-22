
/***********************************************************************
 * 
 * 
 * RING AROUND THE ARDUINO: A GUITAR HERO AND PIANO TILES INSPIRED GAME
 * by Maria Molloy
 * 
 * HOW TO PLAY:
    -press the 3rd and 4th buttons at the same time to begin
    -press the button corresponding to the 1st number on the screen. Follow the notes and you will hear the song!
    -to restart the game, simply press the 3rd and 4th buttons together again
 * 
 * 
*************************************************************************/

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int switchPin0 = 5; //furthest pin right
const int switchPin1 = 4;
const int switchPin2 = 3;
const int switchPin3 = 2; //furthest pin left

int sState1 = 0;
int sState2 = 0;
int prevSwitchState0 = 0;
int prevSwitchState1 = 0;

const int piezoPin = 6;
const int tempo = 100;

const int a = 440;
const int b = 466;
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;

const int pin0note = a; //a
const int pin1note = g; //g
const int pin2note = e; //e
const int pin3note = c; //c

#define LCD_contrast 7 //contrast pin is connected to pin 3
const int contrast = 50; //screen contrast always starts at 50

//Ring Around the Rosy note sequence
int song1[19] = {
  3, 3, 2, 4, 3, 2, 3, 3, 2, 4, 3, 2, 3, 2, 3, 2, 3, 3, 1
};

//Debooucing helpers
int buttonState0;
int buttonState1;
int buttonState2;
int buttonState3;
int lastButtonState0 = LOW;
int lastButtonState1 = LOW;
int lastButtonState2 = LOW;
int lastButtonState3 = LOW;

unsigned long lastDebounceTime0 = 0;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long debounceDelay = 50;

int screen = 1; //start screen
int count = 0; //start at first note

void setup() {

  lcd.begin(16, 2);

  pinMode(switchPin0, INPUT); 
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);

  //Set contrast
  pinMode(LCD_contrast, OUTPUT);
  analogWrite(LCD_contrast, contrast);
}

void loop() {
  //Call changeScreen to start game and load first game
  changeScreen(screen);

  //Read current state of both right pins to enable screen changes
  int reading0 = digitalRead(switchPin0);
  int reading1 = digitalRead(switchPin1);
/*  int reading2 = digitalRead(switchPin2);
  int reading3 = digitalRead(switchPin3); */

  //Check for noise
  if (reading0 != prevSwitchState0) {
    lastDebounceTime0 = millis();
  }
  if (reading1 != prevSwitchState1) {
    lastDebounceTime1 = millis();
  }
  
  if (((millis() - lastDebounceTime0) > debounceDelay) && ((millis() - lastDebounceTime1) > debounceDelay)) {
    //If state changes
    if ((reading0 != sState1) && (reading1 != sState2)) {
      sState1 = reading0;
      sState2 = reading1;

      //If both buttons are pressed
      if ((sState1 == HIGH) && (sState2 == HIGH)) {
        if (screen == 3) {
          screen = 1;
          lcd.clear();
        }
        else {
          screen++;
          lcd.clear();
        }
      }
    }
  }

  //Save reading for next run of loop
  prevSwitchState0 = reading0;
  prevSwitchState1 = reading1;
}

//Function to debounce each button and play the correct note
void playGame(){
  //Read button input
  int reading0 = digitalRead(switchPin0);
  int reading1 = digitalRead(switchPin1);
  int reading2 = digitalRead(switchPin2);
  int reading3 = digitalRead(switchPin3);

  //reset deboucing time
  if (reading0 != lastButtonState0) {
    lastDebounceTime0 = millis();
  }
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();
  }
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }
  if (reading3 != lastButtonState3) {
    lastDebounceTime3 = millis();
  }

  //Debounce 4th button
  if ((millis() - lastDebounceTime0) > debounceDelay) {
    if (reading0 != buttonState0) {
      buttonState0 = reading0;
      //If button is pressed and correct note is being played
      if (buttonState0 == HIGH && song1[count] == 4) {
        tone(piezoPin, pin0note, tempo);
        printScreen();
      }
    }
  }

  //Debounce 3rd button
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      //If button is pressed and correct note is being played
      if (buttonState1 == HIGH && song1[count] == 3) {
        tone(piezoPin, pin1note, tempo);
        printScreen();
      }
    }
  }

  //Debounce 2nd button
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      //If button is pressed and correct note is being played
      if (buttonState2 == HIGH && song1[count] == 2) {
        tone(piezoPin, pin2note, tempo);
        printScreen();
      }
    }
  }  

  //Debounce 1st button
  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != buttonState3) {
      buttonState3 = reading3;
      //If button is pressed and correct note is being played
      if (buttonState3 == HIGH && song1[count] == 1) {
        screen++;
        tone(piezoPin, pin3note, tempo);
        printScreen();
      }
    }
  }
  //Save the readings for next loop run
  lastButtonState0 = reading0;
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;

}

//Function to move to the next note when the correct button is pressed
void printScreen(){
  count++;
  lcd.scrollDisplayLeft();
}

//Function to control the screens.
void changeScreen(int s) {
  //screen 1 = welcome screen
  if (s == 1) {
    count = 0;
    lcd.setCursor(0, 0);
    lcd.print("press both right");
    lcd.setCursor(0, 1);
    lcd.print("buttons to start");
  }
  //screen 2 = game 
  else if (s == 2){
    lcd.setCursor(0, 0);
    //Print sequence of notes on the screen
    for (int i = 0; i < 19; i++){
      lcd.print(song1[i]);
    }
   delay(100);
   playGame();
  }
  //screen 3 = game over
  else {
    lcd.setCursor(19, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(19, 1);
    lcd.print("play again?");
  }
}
