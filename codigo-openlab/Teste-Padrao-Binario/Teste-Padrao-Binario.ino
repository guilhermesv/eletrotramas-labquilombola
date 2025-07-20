#include <FastLED.h>

// Definições
#define LED_PIN     4
#define NUM_LEDS    1200
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// Padrão binário

const int patternLength = strlen(pattern);
int t = NUM_LEDS * 5;

void setup() {
  // Inicializa a fita de LED
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Repete o padrão ao longo da fita de LED
  for (int i = 0; i < NUM_LEDS; i++) {
    int patternIndex = (i + t / 2) % patternLength;
    if (pattern[patternIndex] == '1') {
      leds[i] = CRGB::White;  // LED ligado (branco)
    }
  }

  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 100);
  }

  FastLED.show();

  delay(100);
  t++;
}