/*
TrinketKeyboard debounced one button test

modified version of Arduino Debounce Tutorial https://www.arduino.cc/en/Tutorial/Debounce
rewriten to work with Adafruit Trinket
and Trinket USB Keyboard, https://learn.adafruit.com/trinket-usb-keyboard/code
using Adafruit-Trinket-USB library, https://github.com/adafruit/Adafruit-Trinket-USB/

a momentary pushbutton is connected to pin #0 and GND,
taps/pushes on button are debounced.
*/
    
#include <TrinketKeyboard.h>
    
#define buttonPin 0
  
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);

  // set initial LED state
  digitalWrite(buttonPin, HIGH);
  
  // start USB stuff
  TrinketKeyboard.begin();

}

void loop() {
    // the poll function must be called at least once every 10 ms
    // or cause a keystroke
    // if it is not, then the computer may think that the device
    // has stopped working, and give errors
    TrinketKeyboard.poll();
    
    // read the state of the switch into a local variable:
    int reading = digitalRead(buttonPin);
    
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH),  and you've waited
    // long enough since the last press to ignore any noise:
    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
        }
    if ((millis() - lastDebounceTime) > debounceDelay) {
        // whatever the reading is at, it's been there for longer
        // than the debounce delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;
            
            // only toggle the LED if the new button state is HIGH
            if (buttonState == HIGH) {
                // type out string 
                TrinketKeyboard.print("Hello!");
                }
            }
        }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}       

