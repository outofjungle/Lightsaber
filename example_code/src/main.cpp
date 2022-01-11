#include <Arduino.h>
#include <FastLED.h>

#if TARGET_CHIPSET == ATTINY85
#define CLOCK_PIN 2
#define DATA_PIN 0
#elif TARGET_CHIPSET == ESP8266
#define CLOCK_PIN 14
#define DATA_PIN 13
#elif TARGET_CHIPSET == ESP32
#define CLOCK_PIN 18
#define DATA_PIN 23
#endif

#define NUM_LEDS 10
#define DELAY 42
#define DELTA_HSV_SHIFT 8

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(0xFF);
}

void update_color()
{
  static uint8_t hue = 0;
  static int8_t pos = 0;
  static int8_t dir = 1;

  hue += DELTA_HSV_SHIFT;

  fill_solid(leds, NUM_LEDS, CRGB::Black); // set all LEDs to black
  leds[pos] = CHSV(hue, 0xFF, 0xFF);       // set the current pos to computed color (saturation=0xFF, value=0xFF)
  blur1d(leds, NUM_LEDS, 0x20);            // blend color to nearest neighbors
  FastLED.show();

  pos = pos + dir;
  if (pos <= 0)
  {
    pos = 0;
    dir = dir * -1;
  }
  else if (pos >= NUM_LEDS)
  {
    pos = NUM_LEDS - 1;
    dir = dir * -1;
  }
}

void loop()
{
  static bool do_update;
  static uint32_t last_updated;

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
