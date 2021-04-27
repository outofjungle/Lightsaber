# Lightsaber

## Wiring for the demo

The APA102 is 5V signaling. Please use appropriate logic level converter if working with 3.3V microcontrollers, like ESP8266 or ESP32. APA102 is controlled via the SPI bus.

| Lightsaber Pin | Microcontroller Pin |
|----------------|---------------------|
| GND            | GND                 |
| VCC            | 5V                  |
| CI             | SCK                 |
| DI             | MOSI                |
