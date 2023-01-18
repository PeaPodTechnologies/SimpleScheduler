#include <Arduino.h>

#define NUM_TIMERS          2

#define PIN_WATERING        2
#define DELAY_WATERING_ON   10000     // 10 seconds
#define DELAY_WATERING_OFF  1790000   // 29 minutes 50 seconds
#define PERIOD_WATERING     (DELAY_WATERING_ON + DELAY_WATERING_OFF)

#define PIN_LIGHTING        9
#define DELAY_LIGHTING_ON   43200000  // 12 hours
#define DELAY_LIGHTING_OFF  43200000  // 12 hours
#define PERIOD_LIGHTING     (DELAY_LIGHTING_ON + DELAY_LIGHTING_OFF)
#define PWM_LIGHTING        (unsigned char)(255*0.1)

void analogWriteWrapper(unsigned char pin, unsigned char pwm) {
  analogWrite(pin, pwm);
}

typedef void (*pin_setter_t)(unsigned char, unsigned char);

typedef struct {
  unsigned long duration;
  unsigned long period;
  unsigned char pin;
  unsigned char on;
  unsigned char off;
  const pin_setter_t& setter;
} scheduler_timer_t;

const scheduler_timer_t timers[NUM_TIMERS] = {
  {
    .duration = DELAY_WATERING_ON,
    .period = PERIOD_WATERING,
    .pin = PIN_WATERING,
    .on = HIGH,
    .off = LOW,
    .setter = &digitalWrite
  },
  {
    .duration = DELAY_LIGHTING_ON,
    .period = PERIOD_LIGHTING,
    .pin = PIN_LIGHTING,
    .on = PWM_LIGHTING,
    .off = LOW,
    .setter = &analogWriteWrapper
  }
};

void setup() {
  for(int i = 0; i < NUM_TIMERS; i++) {
    pinMode(timers[i].pin, OUTPUT);
  }
  
  delay(1000);
}

void loop() {
  for(int i = 0; i < NUM_TIMERS; i++) {
    if(millis() % timers[i].period <= timers[i].duration) {
      Serial.print("Timer ");
      Serial.print(i);
      Serial.println(" ON");
      timers[i].setter(timers[i].pin, timers[i].on);
    } else {
      Serial.print("Timer ");
      Serial.print(i);
      Serial.println(" OFF");
      timers[i].setter(timers[i].pin, timers[i].off);
    }
  }

  delay(10);
}