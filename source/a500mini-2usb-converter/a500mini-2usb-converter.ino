/*
   c64mini-arcade2usb-converter.ino

   A500 Mini Arcade Joystick to USB Converter.

   Version 1.1 (See CHANGELOG)
   Release date: 2019-04-19

   Written & released by M.F. Wieland (TSB)

   Licensed under the MIT License. See LICENSE file in the project root for full license information.

   ====================================================

   Adapted to work on the A500 mini by Shadowtrance April 2022
*/

/*
'THEGamepad' |  Mapping in windows  |  DB9 (DE9) PIN
    Up       |         Up           |      1
   Down      |        Down          |      2
   Left      |        Left          |      3
   Right     |        Right         |      4

    X        |       Button 4       |      5 (POTX...Button 3) - also external extra button
    A        |       Button 3       |      6 (Button 1)
    -        |          -           |      7 (+5v)
    -        |          -           |      8 (GND)
    B        |       Button 2       |      9 (POTY...Button 2)
    Y        |       Button 1       |      external extra button

   Menu      |       Button 7       |      external extra button
   Home      |       Button 8       |      external extra button

    L        |       Button 5       |      external extra button
    R        |       Button 6       |      external extra button
*/

//Custom board VID 0x22BA PID 0x1020 works on an unmodded A500 mini

#include "joystick.h"

// define buttons
const int pin_joystick_up = 2;            //UP
const int pin_joystick_down = 3;          //DOWN
const int pin_joystick_left = 4;          //LEFT
const int pin_joystick_right = 5;         //RIGHT

const int pin_joystick_button_a = 6;      //A
const int pin_joystick_button_b = 7;      //B
const int pin_joystick_button_x = 10;     //X
const int pin_joystick_button_y = 8;      //Y

const int pin_joystick_button_menu = 18;  //MENU - Pin 18 is usually labelled as A0
const int pin_joystick_button_home = 15;  //HOME

const int pin_joystick_button_l = 16;     //L
const int pin_joystick_button_r = 14;     //R

int debounceDelay = 1; // debounce delay

void setup() {

  // setup input pins
  pinMode(pin_joystick_up, INPUT_PULLUP);
  pinMode(pin_joystick_down, INPUT_PULLUP);
  pinMode(pin_joystick_left, INPUT_PULLUP);
  pinMode(pin_joystick_right, INPUT_PULLUP);

  pinMode(pin_joystick_button_a, INPUT_PULLUP);
  pinMode(pin_joystick_button_b, INPUT_PULLUP);
  pinMode(pin_joystick_button_x, INPUT_PULLUP);
  pinMode(pin_joystick_button_y, INPUT_PULLUP);

  pinMode(pin_joystick_button_menu, INPUT_PULLUP);
  pinMode(pin_joystick_button_home, INPUT_PULLUP);

  pinMode(pin_joystick_button_l, INPUT_PULLUP);
  pinMode(pin_joystick_button_r, INPUT_PULLUP);
}

void loop() {

  // Reset values for next loop..
  Joystick.reset();
  
  //=====================================================

  // Button - Up
  if (digitalRead(pin_joystick_up) == LOW) {
    Joystick.up();
  }

  // Button - Down
  if (digitalRead(pin_joystick_down) == LOW) {
    Joystick.down();
  }

  // Button - Left
  if (digitalRead(pin_joystick_left) == LOW) {
    Joystick.left();
  }

  // Button - Right
  if (digitalRead(pin_joystick_right) == LOW) {
    Joystick.right();
  }

  //=====================================================

  // Button - A
  if (digitalRead(pin_joystick_button_a) == LOW) {
    Joystick.button_press(0x0004);
  }

  // Button - B
  if (digitalRead(pin_joystick_button_b) == LOW) {
    Joystick.button_press(0x0002);
  }

  // Button - X
  if (digitalRead(pin_joystick_button_x) == LOW) {
    Joystick.button_press(0x0008);
  }

  // Button - Y
  if (digitalRead(pin_joystick_button_y) == LOW) {
    Joystick.button_press(0x0001);
  }

  //=====================================================
  
  // Button - Menu
  if (digitalRead(pin_joystick_button_menu) == LOW) {
    Joystick.button_press(0x0100); //Corresponds to button 9 in windows but menu on the A500 mini
    //Joystick.button_press(0x0040); //Corresponds to button 7 in windows but not on the A500 mini
  }

  // Button - Home
  if (digitalRead(pin_joystick_button_home) == LOW) {
    Joystick.button_press(0x0200); //Corresponds to button 10 in windows but home on the A500 mini
    //Joystick.button_press(0x0080); //Corresponds to button 8 in windows but not on the A500 mini
  }

  //=====================================================
  
  // Button - L
  if (digitalRead(pin_joystick_button_l) == LOW) {
    Joystick.button_press(0x0010);
  }

  // Button - R
  if (digitalRead(pin_joystick_button_r) == LOW) {
    Joystick.button_press(0x0020);
  }

  // update joystick actions
  Joystick.usb_update();

  delay(debounceDelay);
}
