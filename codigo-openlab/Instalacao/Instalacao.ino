#include <arduinoFFT.h>
#include <FastLED.h>

// CONFIGURACAO ESP E FITA
#define LED_PIN     4   
#define MIC_PIN     34
#define NUM_LEDS    1200 //192
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

// CONFIGURACAO FREQ
#define F_SAMPLES     512     // Número de amostras da FFT (deve ser uma potência de 2)
#define F_SAMPLING_FREQUENCY 40000 // Frequência de amostragem em Hz
double vReal[F_SAMPLES];
double vImag[F_SAMPLES];
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, F_SAMPLES, F_SAMPLING_FREQUENCY);

// CONFIGURACAO AMPLI
int A_RUIDO_LIMITE = 1000; // Nenhum som abaixo dessa amplitude sera considerado
int A_NOISE_LIMIAR = 150; // Valor de brilho para aparecer o noise
#define A_SAMPLES 100 // Número de amostras para cálculo da média

// CONFIGURACAO TEMP

// TIMER 1
unsigned long previousMillis_1 = 0;
const long interval_1 = 1000; // 60.000 ms = 1 minuto
int t_1 = 0;

// TIMER 2
unsigned long previousMillis_2 = 0;
const long interval_2 = 10000; // 60.000 ms = 1 minuto
int t_2 = 0;


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

  // Rodando padroes em loop

  // EVERY_N_MILLISECONDS(10) {
  //   blend(leds_src_1, leds_src_2, leds_out, NUM_LEDS, blend_qtd);    // Blend between the two sources
  //   if (src_1_ativa) {
  //     if (blend_qtd < 255) blend_qtd++;                          // Blend 'up' to source 2
  //   } else {
  //     if (blend_qtd > 0) blend_qtd--;                            // Blend 'down' to source 1
  //   }
  // }

  // EVERY_N_SECONDS(5) {
  //   efeito_proximo();
  // }

  // efeito_run(efeito_src_1, leds_src_1);                  // Run both patterns simultaneously
  // efeito_run(efeito_src_2, leds_src_2);

  // Rodando padrão únicos
  efeito_run(1, leds_out);

  FastLED.show();
  incrementa_tempo();
  delay(50);
}
