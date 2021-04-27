#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 9
#define CLOCK_PIN 14
#define DATA_PIN 13

CRGB leds[NUM_LEDS];

void set_color(CRGB color) {
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = color;
  }
}

void setup() {
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
}

void loop() {
  set_color(CRGB::Red);
  FastLED.show();
  delay(500);

  set_color(CRGB::Green);
  FastLED.show();
  delay(500);

  set_color(CRGB::Blue);
  FastLED.show();
  delay(500);
}
