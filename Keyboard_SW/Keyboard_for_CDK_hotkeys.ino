The MIT License (MIT)
Copyright @ 2026 Andriy Melnykov
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.


// Arduino board: ProMicro 5V / 16 MHz
// Connections:
//Arduino #9  - key1 -
//Arduino #8  - key2 +
//Arduino #7  - key3 P
//Arduino #6  - key4 M
//Arduino #5  - key5 Z
//Arduino #4  - key6 B
//common for keys - GND

//LED DIO - pin A3
//LED +5V - pin RAW
//LED GND - pin GND

#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

#define LED_DO    21
#define LED_COUNT  7

Adafruit_NeoPixel strip(LED_COUNT, LED_DO, NEO_GRB + NEO_KHZ800);

// RGB values for each LED as constants
const uint8_t LED1_R = 15;
const uint8_t LED1_G = 1;
const uint8_t LED1_B = 0;

const uint8_t LED2_R = 15;
const uint8_t LED2_G = 1;
const uint8_t LED2_B = 0;

const uint8_t LED3_R = 15;
const uint8_t LED3_G = 1;
const uint8_t LED3_B = 0;

const uint8_t LED4_R = 0;
const uint8_t LED4_G = 0;
const uint8_t LED4_B = 0;

const uint8_t LED5_R = 15;
const uint8_t LED5_G = 1;
const uint8_t LED5_B = 0;

const uint8_t LED6_R = 15;
const uint8_t LED6_G = 1;
const uint8_t LED6_B = 0;

const uint8_t LED7_R = 15;
const uint8_t LED7_G = 1;
const uint8_t LED7_B = 0;


int LED_pin = 17;  // The RX LED has a defined Arduino pin
int key1_pin = 9;
int key2_pin = 8;
int key3_pin = 7;
int key4_pin = 6;
int key5_pin = 5;
int key6_pin = 4;
int cycle_delay = 10;

int key1=1;
int key2=1;
int key3=1;
int key4=1;
int key5=1;
int key6=1;

int key1_old=1;
int key2_old=1;
int key3_old=1;
int key4_old=1;
int key5_old=1;
int key6_old=1;


void sendHotkey(uint8_t key) {
  Keyboard.releaseAll();
  delay(30);

  Keyboard.press(KEY_LEFT_CTRL);
  delay(10);

  Keyboard.press(KEY_LEFT_ALT);
  delay(30);
  
  //Keyboard.press(KEY_LEFT_SHIFT);

  Keyboard.press(key);
  delay(100);
  
  Keyboard.release(key);
  delay(100);

  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_LEFT_CTRL);
  delay(40);        // small gap before next possible hotkey

  Serial.print("Arduino detected button ");
  Serial.println(key + 1);
}


void setup() {
  pinMode(LED_pin, OUTPUT);  // Set RX LED as an output
  digitalWrite(LED_pin, HIGH);

  pinMode(key1_pin, INPUT_PULLUP);
  pinMode(key2_pin, INPUT_PULLUP);
  pinMode(key3_pin, INPUT_PULLUP);
  pinMode(key4_pin, INPUT_PULLUP);
  pinMode(key5_pin, INPUT_PULLUP);
  pinMode(key6_pin, INPUT_PULLUP);

  //Keyboard.begin(KeyboardLayout_de_DE);
  Keyboard.begin();

  strip.begin();
  strip.show(); // Initialize all LEDs to off

  // Set colors for all 7 LEDs
  strip.setPixelColor(0, strip.Color(LED1_R, LED1_G, LED1_B));
  strip.setPixelColor(1, strip.Color(LED2_R, LED2_G, LED2_B));
  strip.setPixelColor(2, strip.Color(LED3_R, LED3_G, LED3_B));
  strip.setPixelColor(3, strip.Color(LED4_R, LED4_G, LED4_B));
  strip.setPixelColor(4, strip.Color(LED5_R, LED5_G, LED5_B));
  strip.setPixelColor(5, strip.Color(LED6_R, LED6_G, LED6_B));
  strip.setPixelColor(6, strip.Color(LED7_R, LED7_G, LED7_B));

  // Send data once after startup
  strip.show();

  Serial.begin(115200);
}

void loop() {
  key1 = digitalRead(key1_pin);
  key2 = digitalRead(key2_pin);
  key3 = digitalRead(key3_pin);
  key4 = digitalRead(key4_pin);
  key5 = digitalRead(key5_pin);
  key6 = digitalRead(key6_pin);
  
  if ((key1 == 0) && (key1_old == 1)) { 
    sendHotkey(KEY_F13);
  }

  if ((key2 == 0) && (key2_old == 1)) { 
    sendHotkey(KEY_F14);
  }

  if ((key3 == 0) && (key3_old == 1)) { 
    sendHotkey(KEY_F15);
  }

  if ((key4 == 0) && (key4_old == 1)) { 
    sendHotkey(KEY_F16);
  }

  if ((key5 == 0) && (key5_old == 1)) { 
    sendHotkey(KEY_F17);
  }

  if ((key6 == 0) && (key6_old == 1)) { 
    sendHotkey(KEY_F18);
  }

  key1_old = key1;
  key2_old = key2;
  key3_old = key3;
  key4_old = key4;
  key5_old = key5;
  key6_old = key6;
  
  delay(cycle_delay);
}
