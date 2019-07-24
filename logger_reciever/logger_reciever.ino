// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include "Keyboard.h"

void setup() {
  Wire.begin(0);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Keyboard.begin();
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  if(howMany != 2) {
    Serial.println("invalid keystroke data"); 
  }
  char type = Wire.read();  
  Serial.print("Type of keystroke:");
  Serial.print(type);
  Serial.print("   keystroke:");
  char keystroke = Wire.read();
  Serial.print(keystroke);
  Serial.println();
    // receive byte as an integer
  //Serial.println(x);         // print the integer
  if( type == 'P') {
    Keyboard.press(keystroke);
  } else if ( type == 'R') {
    Keyboard.release(keystroke);
  }
}
