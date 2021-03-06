/*
  11/12/19
  Project Part 1 by Maria Molloy
  This project is a byte calculator where a user inputs two bytes using buttons and they are added together. 
  The user can also adjust the contrast of the LCD screen. 
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //each pin the LCD is wired to

const int switchPin1 = 8; //switch1
const int switchPin2 = 9; //switch2
int sState1 = 0;
int sState2 = 0;
int prevSwitchState1 = 0;
int prevSwitchState2 = 0;

int screen = 0;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 50;

int input1[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //first byte user inputs
int input2[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //second byte user inputs
int solution[9]; //sum of two bytes

int prevBit = 0; //while collecting input, if the bit on the screen is 1 or 0
int currentBit = 0; //while collecting input, which bit user is currently changing

#define LCD_contrast 6 //contrast pin is connected to pin 3
const int startCont = 50; //screen contrast always starts at 50
int contrast = 50;

void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);

  //Set pin 6 as the contrast pin and set initial screen contrast
  pinMode(LCD_contrast, OUTPUT);
  analogWrite(LCD_contrast, startCont);
}

void loop() {

  //call the function to display each screen
  changeScreen(screen);

  //get readings for each switch
  int reading1 = digitalRead(switchPin1);
  int reading2 = digitalRead(switchPin2);

  // If the switch changed, due to noise or pressing, reset the debouncing timer
  if (reading1 != prevSwitchState1) {
    lastDebounceTime1 = millis();
  }
  if (reading2 != prevSwitchState2) {
    lastDebounceTime2 = millis();
  }

  // if reading has been there longer than the debounce delay, we can take the reading
  if (((millis() - lastDebounceTime1) > debounceDelay) && ((millis() - lastDebounceTime2) > debounceDelay)) {

    // if the switch state has changed:
    if ((reading1 != sState1) && (reading2 != sState2)) {
      sState1 = reading1;
      sState2 = reading2;

      // if both switches are HIGH, change to next screen
      if ((sState1 == HIGH) && (sState2 == HIGH)) {
        if (screen == 4) {
          screen = 0;
          lcd.clear();
        }
        else {
          screen++;
          lcd.clear();
        }
      }
    }
  }
  // save the reading for the next time the loop runs
  prevSwitchState1 = reading1;
  prevSwitchState2 = reading2;
}

//function to call each screen
// s = which screen LCD is on
void changeScreen (int s) {

  int switchState1 = digitalRead(switchPin1);
  int switchState2 = digitalRead(switchPin2);

  //Welcome/Splash Screen
  //User moves to next screen by pressing both buttons
  if (s == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Hello!Press both");
    lcd.setCursor(0, 1);
    lcd.print("buttons to start");

    // Reset both inputs back to 00000000
    for (int i = 0; i < 8; i++) {
      input1[i] = 0;
      input2[i] = 0;
    }
  }

  //Second screen: user enters first bit
  //User moves to next screen by pressing switch 2 after inputing 8th bit
  else if (s == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Enter byte 1");
    for (int i = 0; i < 8; i++) {
      lcd.setCursor(i, 1);
      lcd.print(input1[i]);
    }

    // reset the debouncing timer for switch 1
    if (switchState1 != prevSwitchState1) {
      lastDebounceTime1 = millis();
    }

    // Whatever reading is, its been there longer than the debounce delay so we can take the current reading
    if ((millis() - lastDebounceTime1) > debounceDelay) {

      // if the button state has changed:
      if (switchState1 != sState1) {
        sState1 = switchState1;

        //if button 1 is pressed, change the bit from 0 to 1 or vice versa
        if (sState1 == HIGH && screen == 1) {
          //if you are changing the bit from 0 to 1
          if (prevBit == 0) {
            //go through the array and print out each bit and change the one you are trying to change
            for (int i = 0; i < 8; i++) {
              if (i == currentBit) {
                lcd.setCursor(currentBit, 1);
                lcd.print("1");
                input1[currentBit] = 1;
              }
              else {
                lcd.setCursor(i, 1);
                lcd.print(input1[i]);
              }
            }
            prevBit = 1;
          }
          //if you are changing the bit from 1 to 0
          else {
            //go through the array and print out each bit and change the one you are trying to change
            for (int i = 0; i < 8; i++) {
              if (i == currentBit) {
                lcd.setCursor(currentBit, 1);
                lcd.print("0");
                input1[currentBit] = 0;
              }
              else {
                lcd.setCursor(i, 1);
                lcd.print(input1[i]);
              }
            }
            prevBit = 0;
          }
        }
      }
    }

    // reset the debouncing timer for switch 2
    if (switchState2 != prevSwitchState2) {
      lastDebounceTime2 = millis();
    }

    // whatever the reading is, its been there longer than the debounce delay so we can take the reading
    if ((millis() - lastDebounceTime2) > debounceDelay) {

      // if the button state has changed:
      if (switchState2 != sState2) {
        sState2 = switchState2;
        // if button 2 is pressed, move to change next bit, unless you have changed the last bit, then move to the next screen
        if (sState2 == HIGH && screen == 1) {
          if (currentBit < 8) {
            currentBit++;
          }
          else {
            currentBit = 0;
            prevBit = 0;
            screen++;
          }
        }
      }
    }

    // save the reading for the next loop
    prevSwitchState1 = switchState1;
    prevSwitchState2 = switchState2;
  }

  // Third screen: user enters second bit
  // User moves to the next screen by pressing switch 2 after inputing the 8th bit
  else if (s == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Enter byte 2");
    for (int i = 0; i < 8; i++) {
      lcd.setCursor(i, 1);
      lcd.print(input2[i]);
    }

    // reset the debouncing timer for switch 1
    if (switchState1 != prevSwitchState1) {
      lastDebounceTime1 = millis();
    }

    // whatever the reading is, its been longer than the debounce delay so we can take the reading
    if ((millis() - lastDebounceTime1) > debounceDelay) {

      // if the button state has changed:
      if (switchState1 != sState1) {
        sState1 = switchState1;

        //if button 1 is pressed, change the bit from 0 to 1 or vice versa
        if (sState1 == HIGH && screen == 2) {
          //if you are changing from 0 to 1
          if (prevBit == 0) {
            //go through the array and print out each bit and change the one you are trying to change
            for (int i = 0; i < 8; i++) {
              if (i == currentBit) {
                lcd.setCursor(currentBit, 1);
                lcd.print("1");
                input2[currentBit] = 1;
              }
              else {
                lcd.setCursor(i, 1);
                lcd.print(input2[i]);
              }
            }
            prevBit = 1;
          }
          //if you are changing the bit from 1 to 0
          else {
            //go through the array and print out each bit and change the one you are trying to change
            for (int i = 0; i < 8; i++) {
              if (i == currentBit) {
                lcd.setCursor(currentBit, 1);
                lcd.print("0");
                input2[currentBit] = 0;
              }
              else {
                lcd.setCursor(i, 1);
                lcd.print(input2[i]);
              }
            }
            prevBit = 0;
          }
        }
      }
    }

    // reset the debouncing timer for switch 2
    if (switchState2 != prevSwitchState2) {
      lastDebounceTime2 = millis();
    }

    // whatever the reading is, its been longer than the debounce delay so we can take the reading
    if ((millis() - lastDebounceTime2) > debounceDelay) {

      // if the button state has changed:
      if (switchState2 != sState2) {
        sState2 = switchState2;
        // if button 2 is pressed, move to change next bit, unless you have changed the last bit, then move to the next screen
        if (sState2 == HIGH && screen == 2) {
          if (currentBit < 8) {
            currentBit++;
          }
          else {
            currentBit = 0;
            prevBit = 0;
            screen++;
          }
        }
      }
    }
    // save the reading for the next loop
    prevSwitchState1 = switchState1;
    prevSwitchState2 = switchState2;
  }

  //Fourth screen: the bytes are added and the sum is displayed on the screen
  //The addBits function is called to complete the math to display the solution
  //User moves to the next screen by pressing both buttons
  else if (s == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Your solution is");
    addBits(input1, input2);

    int reading1 = digitalRead(switchPin1);
    int reading2 = digitalRead(switchPin2);

    // reset both debouncing timers
    if (reading1 != prevSwitchState1) {
      lastDebounceTime1 = millis();
    }
    if (reading2 != prevSwitchState2) {
      lastDebounceTime2 = millis();
    }

    // whatever the reading is, its been longer than the debounce delay so we can take the reading
    if (((millis() - lastDebounceTime1) > debounceDelay) && ((millis() - lastDebounceTime2) > debounceDelay)) {

      // if the button state has changed:
      if ((reading1 != sState1) && (reading2 != sState2)) {
        sState1 = reading1;
        sState2 = reading2;

        //Move to the next screen if both buttons are pressed
        if ((sState1 == HIGH) && (sState2 == HIGH)) {
          screen = 4;
        }
      }
    }
    // save the reading for the next time the loop runs
    prevSwitchState1 = reading1;
    prevSwitchState2 = reading2;
  }

  //Fifth screen: user can adjust screen contrast
  //User can adjust the contrast of the screen by pressing the buttons
  // User moves back to the splash screen and the calculator is reset by pressing both buttons
  else if (s == 4) {
    lcd.setCursor(0, 0);
    lcd.print("Change contrast:");
    lcd.setCursor(0, 1);
    lcd.print("Switch1-");
    lcd.setCursor(8, 1);
    lcd.print("Switch2+");

    //reset both debouncing timers
    if (switchState1 != prevSwitchState1) {
      lastDebounceTime1 = millis();
    }
    if (switchState2 != prevSwitchState2) {
      lastDebounceTime2 = millis();
    }

    // whatever the reading is, its been longer than the debounce delay so we can take the reading
    if ((millis() - lastDebounceTime1) > debounceDelay) {
      if (switchState1 != sState1) {
        sState1 = switchState1;

        //decrease contrast if button 1 is pressed
        if (sState1 == HIGH) {
          //if the contrast is less than the maximum contrast value, decrease contrast
          if (contrast < 120) {
            contrast = contrast + 10;
            pinMode(LCD_contrast, OUTPUT);
            analogWrite(LCD_contrast, contrast);
          }
        }
      }
    }

    // whatever the reading is, its been longer than the debounce delay so we can take the reading
    if ((millis() - lastDebounceTime2) > debounceDelay) {
      if (switchState2 != sState2) {
        sState2 = switchState2;

        //heighten contrast if button 2 is pressed
        if (sState2 == HIGH) {
          //if the contrast value is greater than the lowest contrast value, heighten the contrast
          if (contrast > 20) {
            contrast = contrast - 10;
            pinMode(LCD_contrast, OUTPUT);
            analogWrite(LCD_contrast, contrast);
          }
        }
      }
    }
    // save the reading for the next time the loop runs
    prevSwitchState1 = switchState1;
    prevSwitchState2 = switchState2;
  }
}

// Function to add the two input bytes
// addend1 = the first input byte
// addend2 = the second input byte
void addBits(int addend1[], int addend2[]) {

  //keeps track if there's a bit to carry
  int carry = 0;

  //go through the arrays and add each bit
  for (int i = 7; i >= 0; i--) {
    //if both bits are 1
    if (addend1[i] == 1 && addend2[i] == 1) {
      //if there's a carry, sum = 1, carry = 1
      if (carry == 1) {
        solution[i + 1] = 1;
      }
      //if no carry, sum = 0, carry = 1
      else {
        solution[i + 1] = 0;
        carry = 1;
      }
    }
    //if both bits are 0
    else if (addend1[i] == 0 && addend2[i] == 0) {
      //if there's a carry, sum = 1, carry = 0
      if (carry == 1) {
        solution[i + 1] = 1;
        carry = 0;
      }
      //if no carry, sum = 0, carry = 0
      else {
        solution[i + 1] = 0;
      }
    }
    //if one bit = 0 and one bit = 1
    else {
      //if there's a carry, sum = 0, carry = 1
      if (carry == 1) {
        solution[i + 1] = 0;
      }
      //if no carry, sum = 1, carry = 0
      else {
        solution[i + 1] = 1;
      }
    }
  }
  //if carry = 1 after all 8 bits are added, then the solution has 9 bits, where the first = 1
  if (carry == 1) {
    solution[0] = 1;
  }

  //print out the solution
  for (int i = 0; i < 9; i++) {
    lcd.setCursor(i, 1);
    lcd.print(solution[i]);
    Serial.print(solution[i]);
  }
}
