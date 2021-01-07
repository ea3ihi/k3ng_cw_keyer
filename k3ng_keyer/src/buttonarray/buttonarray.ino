// Button Array test

#include "buttonarray.h"

#define ARRAY_PIN 13
#define NB_BUTTONS 5
#define ENCODER_PIN 0


int button_array_high_limit[NB_BUTTONS];
int button_array_low_limit[NB_BUTTONS];
long button_depress_time;



ButtonArray button_array(ARRAY_PIN, NB_BUTTONS, false);
ButtonArray encoder(ENCODER_PIN, 1, false);

void setup() {
  Serial.begin(115200);
  delay(1000); 
  button_array.AddAll();
  encoder.AddAll();

  while(1) {
    int x = analogRead(ARRAY_PIN);
    Serial.println(x);
  }
}

void loop() {
  
  int analogbuttontemp = button_array.Pressed();
  if (encoder.Pressed() == 0) {
    Serial.println("encoder pressed ");
  }
  if (analogbuttontemp >= 0 ) {
    // button pressed.

    button_depress_time = button_array.last_pressed_ms;

    while (button_array.Held(analogbuttontemp, button_depress_time + 1000)) {

    }
    if (millis() - button_depress_time  < 400) {
      Serial.print("button pressed ");
      Serial.println(analogbuttontemp);
    } else {
      Serial.print("button ");
      Serial.print(analogbuttontemp);
      Serial.print(" held for ");
      Serial.println(millis() - button_depress_time);
    }
  }
}
