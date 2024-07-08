/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "USBKeyboard.h"

const int buttonPin = PIN_PUSH_BUTTON;         // input pin for pushbutton
int previousButtonState = HIGH;  // for checking the state of a pushButton
int counter = 0;                 // button push counter

void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT);
  // initialize control over the keyboard:
  USBKeyboard.begin();
}

void loop() {
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if ((buttonState != previousButtonState)
      // and it's currently pressed:
      && (buttonState == HIGH)) {
    // increment the button counter
    counter++;
    // type out a message
    USBKeyboard.print("You pressed the button ");
    USBKeyboard.print(counter);
    USBKeyboard.println(" times.");
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}
