#include <FastLED.h>

// DEFINICOES
#define ledPin 4      // Porta Digital
#define NUM_LEDS 192  // Numero de leds
CRGB leds[NUM_LEDS];  // Cria array de leds
uint8_t brilho[NUM_LEDS] = { 0 };
int c = 0;

uint8_t paleta_inicio = 0;
DEFINE_GRADIENT_PALETTE(r_b){
  0,  255,  0,  0,
  255,  0,  0,  255,
};
CRGBPalette16 paleta = r_b;

void setup() {
  FastLED.addLeds<WS2812, ledPin, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  Serial.begin(9600);

  for (int i = 0; i < NUM_LEDS; i++) {
    brilho[i] = 0;
  }
}

void loop() {

  // Atualiza a cor
  CRGB cor_inicial = ColorFromPalette(paleta, c % 255, 255, LINEARBLEND);
  CHSV cor_hsv = rgb2hsv_approximate(cor_inicial);

  // Atualizar o brilho N leds em sequência N vezes em posições aleatórias
  int leds_aceso = 8;
  int qtd_vezes = 4;
  EVERY_N_MILLISECONDS(1000) {
    for (int i = 0; i < qtd_vezes; i++) {
      int posicao = random16(NUM_LEDS);
      uint8_t posicao_brilho = random8();
      for (int j = 0; j < leds_aceso; j++) {
        int led_indice = (posicao + j) % NUM_LEDS;
        brilho[led_indice] = qadd8(brilho[led_indice], posicao_brilho);
      }
    }
  }

  // Transfere as informações da array de Brilho para a fita e faz o fade
  EVERY_N_MILLISECONDS(20) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(cor_hsv.h, cor_hsv.s, brilho[i]);
      // Replica simples da função fadeToBlackBy() aplicada ao array de brilho
      brilho[i] = scale8(brilho[i], 255 - 10);
    }
  }

  EVERY_N_MILLISECONDS(500) {
    c++;
  }

  FastLED.show();
  // delay(50);
}