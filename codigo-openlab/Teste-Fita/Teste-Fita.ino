#include <FastLED.h>

// DEFINICOES
#define ledPin 4       // Porta Digital
#define NUM_LEDS 864  // Numero de leds
CRGB leds[NUM_LEDS];   // Cria array de leds
int c = 0;

uint8_t paleta_inicio = 0;
DEFINE_GRADIENT_PALETTE(r_b){
  0,   255,    0,    0,
  // 127,   0, 255,   0,
  255,   0,    0,   255,
};

DEFINE_GRADIENT_PALETTE(bk_b_r_w){
  0,     0,   0,   0,
  102,   0,   0, 255,
  191, 255,   0,   0,
  229, 237, 165,  83,
  255, 255, 255, 255,
};

DEFINE_GRADIENT_PALETTE(bk_b_r){
  0,     0,   0,   0,
  102,   0,   0, 255,
  191, 255,   0,   0,
  255, 255,   0,   166,
};

DEFINE_GRADIENT_PALETTE(bk_b_g){
  0,     0,   0,   0,
  102,   0,   0, 255,
  191,   0, 255,   0,
  255, 255,   0,   0,
};

CRGBPalette16 paleta = bk_b_g;

void setup() {
  FastLED.addLeds<WS2812, ledPin, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
  // // Loop Economico
  // for (int dot = 0; dot < NUM_LEDS; dot++) {
  //   leds[dot] = CRGB::Blue;
  //   FastLED.show();
  //   // clear this led for the next time around the loop
  //   leds[dot] = CRGB::Black;
  //   delay(50);
  // }

  // // Loop Economico + Fade 1
  // leds[c%NUM_LEDS] = CRGB::Blue;
  // EVERY_N_MILLISECONDS(20) {
  //   fadeToBlackBy(leds, NUM_LEDS, 20);
  // }
  // FastLED.show();
  // c++;
  // delay(50);

  // Loop Economico + Fade 2
  // leds[c%NUM_LEDS] = CRGB::White;
  // EVERY_N_MILLISECONDS(20) {
  //   fadeToBlackBy(leds, NUM_LEDS, 10);
  // }
  // FastLED.show();
  // c++;
  // delay(10);

  // // Loop Acende tudo Máximo
  // for (int i = 0; i < NUM_LEDS; i++) {
  //   leds[i] = CRGB(255, 0, 255);
  //   // leds[i] = CRGB::Red;
  //   // leds[i] = CRGB::Green;
  //   // leds[i] = CRGB::White;
  // }
  // delay(50);
  // FastLED.show();

  // Loop Paleta
  // fill_palette(leds, NUM_LEDS, paleta_inicio, 1, paleta, 255, LINEARBLEND);
  // EVERY_N_MILLISECONDS(10){
  //   // paleta_inicio++;
  // }
  // FastLED.show();

  // // Loop Paleta Random
  // EVERY_N_MILLISECONDS(50) {
  //   for(int i = 0; i < 50; i++) {
  //     leds[random16(0, NUM_LEDS - 1)] = ColorFromPalette(paleta, random8(), 255, LINEARBLEND);
  //   };
  // }
  // fadeToBlackBy(leds, NUM_LEDS, 20);
  // FastLED.show();


  // Loop Paleta noise
  uint16_t x = 0;
  int scale = 10;
  uint16_t t = millis() / 4;

  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t noise = inoise8(i * scale + x + t);
    leds[i] = ColorFromPalette(paleta, noise, 255, LINEARBLEND);
  }
  FastLED.show();

  //// Loop Noise Simples
  // uint16_t noise_x = 0;
  // uint16_t noise_time = millis() / 4;
  //  fill_noise8(
  //   leds,           // Array de LEDs
  //   NUM_LEDS,       // Número de LEDs
  //   1,              // Octaves (camadas de ruído)
  //   noise_x,        // Posição X no espaço de ruído
  //   30,             // Escala (quanto maior, mais granular)
  //   1,              // Hue octaves (variação de cor)
  //   noise_x,        // Hue x
  //   30,             // Hue scale (variação de cor)
  //   noise_time      // Hue time
  // );
  // FastLED.show();

}
