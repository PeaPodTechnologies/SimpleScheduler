#include <Arduino.h>

#define PIN_WATERING        2
#define DELAY_WATERING_ON   10000     // 10 seconds
#define DELAY_WATERING_OFF  1790000   // 29 minutes 50 seconds
#define PERIOD_WATERING     (DELAY_WATERING_ON + DELAY_WATERING_OFF)

#define PIN_LIGHTING        9
#define DELAY_LIGHTING_ON   43200000  // 12 hours
#define DELAY_LIGHTING_OFF  43200000  // 12 hours
#define PERIOD_LIGHTING     (DELAY_LIGHTING_ON + DELAY_LIGHTING_OFF)
#define PWM_LIGHTING        (255*0.1)

void setup() {
  pinMode(PIN_WATERING, OUTPUT);
  pinMode(PIN_LIGHTING, OUTPUT);
  delay(1000);
}

void loop() {
  if(millis() % PERIOD_WATERING <= DELAY_WATERING_ON) {
    Serial.println("Watering ON");
    digitalWrite(PIN_WATERING, HIGH);
  } else {
    Serial.println("Watering OFF");
    digitalWrite(PIN_WATERING, LOW);
  }

  if(millis() % PERIOD_LIGHTING <= DELAY_LIGHTING_ON) {
    Serial.println("Lighting ON");
    analogWrite(PIN_LIGHTING, PWM_LIGHTING);
  } else {
    Serial.println("Lighting OFF");
    analogWrite(PIN_LIGHTING, 0);
  }

  delay(10);
}