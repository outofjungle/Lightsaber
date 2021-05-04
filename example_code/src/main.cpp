#include <Arduino.h>
#include <FastLED.h>

#if TARGET_CHIPSET == ATTINY85
#define CLOCK_PIN 2
#define DATA_PIN 0
#elif TARGET_CHIPSET == ESP8266
#define CLOCK_PIN 14
#define DATA_PIN 13
#endif
#define NUM_LEDS 10

#define DELAY 42

CRGB leds[NUM_LEDS];

int8_t pos;
int8_t dir;

uint16_t hue = 0;
uint8_t delta = 1;

bool do_update;
uint32_t last_updated;

void setup()
{
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  pos = 0;
  dir = 1;
}

void update_color()
{
  hue += delta;
  hue = hue % 360;

  fill_solid(leds, NUM_LEDS, CRGB::Black); // set all LEDs to black
  leds[pos] = CHSV(hue, 255, 255);         // set the current pos to computed color (saturation=255, value=255)
  blur1d(leds, NUM_LEDS, 32);              // speared color to 2 nearest neighbor
  FastLED.show();

  pos = pos + dir;
  if ((pos < 0) || (pos >= NUM_LEDS))
  {
    dir = dir * -1;
    pos = (pos < 0) ? 0 : pos;
    pos = (pos >= NUM_LEDS) ? NUM_LEDS - 1 : pos;
  }
}

void loop()
{
  if (do_update)
  {
    update_color();

    last_updated = millis();
    do_update = false;
  }

  if (millis() - last_updated > DELAY)
  {
    do_update = true;
  }
}
