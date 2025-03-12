#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


#define LED_PIN 48  // Canvia al pin correcte si cal
#define NUM_LEDS 1  // Si només tens un LED NeoPixel
#define DELAY_TIME 500 // Temps en mil·lisegons


Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
   Serial.begin(115200);
   strip.begin();
   strip.show();
   Serial.println("ESP32-S3 iniciat, NeoPixel parpellejant en vermell...");
}


void loop() {
   // Encén el LED en vermell (RGB: 255, 0, 0)
   strip.setPixelColor(0, strip.Color(255, 0, 0));
   strip.show();
   Serial.println("NeoPixel ENCÈS en vermell!");
   delay(DELAY_TIME);


   // Apaga el LED
   strip.setPixelColor(0, strip.Color(0, 0, 0));
   strip.show();
   Serial.println("NeoPixel APAGAT!");
   delay(DELAY_TIME);
}
