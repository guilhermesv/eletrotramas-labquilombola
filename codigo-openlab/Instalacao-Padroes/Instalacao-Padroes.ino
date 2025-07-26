#include <FastLED.h>

// CONFIGURACAO ESP E FITA
#define LED_PIN     4   
#define MIC_PIN     34
#define NUM_LEDS    192 // 1200 ou 192
#define VOLTS       5
#define MILIAMPS    8000          

CRGB leds_src_1[NUM_LEDS];
CRGB leds_src_2[NUM_LEDS];
CRGB leds_out[NUM_LEDS];

uint8_t blend_qtd = 0;
uint8_t efeito_contador = 0;
uint8_t efeito_src_1 = 0;
uint8_t efeito_src_2 = 1;
bool src_1_ativa = false;

// CONFIGURACAO AMPLI
int A_RUIDO_LIMITE = 1000; // Nenhum som abaixo dessa amplitude sera considerado
int A_NOISE_LIMIAR = 150; // Valor de brilho para aparecer o noise
#define A_SAMPLES 1000 // Número de amostras para cálculo da média

// CONFIGURACAO TEMP

// TIMER 1
unsigned long previousMillis_1 = 0;
const long interval_1 = 60000; // 60.000 ms = 1 minuto
int t_1 = 0;

// TIMER 2
unsigned long previousMillis_2 = 0;
const long interval_2 = 60000; // 60.000 ms = 1 minuto
int t_2 = 127;


// CONFIG GERAL
int t_g = 1000;

void setup() {
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILIAMPS); 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds_out, NUM_LEDS);
  FastLED.clear();
  pinMode(MIC_PIN, INPUT);
  Serial.begin(115200);
  // Começar em um padrão aleatório
  efeito_contador = mod8(random8(), 3);
  efeito_proximo();
}

void loop() {


  // Rodando padrão únicos
  efeito_run(2, leds_out);

  FastLED.show();
  incrementa_tempo();
  delay(50);
}
