#include <FastLED.h>

// DEFINICOES LED
#define LED_PIN 4
#define NUM_LEDS 192

CRGB leds[NUM_LEDS];
uint8_t brilho[NUM_LEDS] = {0};
uint8_t tom[NUM_LEDS] = {0};

int t = 0;

// DEFINICOES MIC
#define MIC_PIN 34   // Pino do microfone
#define SAMPLES 256  // Número de amostras para analisar
#define FAIXA_A 1000
#define FAIXA_B 2000
#define FAIXA_C 3000

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  Serial.begin(115200);
}

void loop() {
  // MIC
  // int amplitude = getAmplitude();  
  int amplitude = getSmoothedAmplitude();  
  int intensidade;

  // LED
  // intensidade = 100;
  intensidade = map(amplitude, 0, 3000, 0, 255);
  intensidade = constrain(intensidade, 0, 255);

  if (amplitude > 0 && amplitude <= FAIXA_A) {
    int pos_inicial = random16(NUM_LEDS);
    for (int i = 0; i < 4; i++) {
      int led_indice = (pos_inicial + i) % NUM_LEDS;
      brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
      tom[led_indice] = 0;
    }
  }

  if (amplitude > FAIXA_A && amplitude <= FAIXA_B) {
    int pos_inicial = random16(NUM_LEDS);
    for (int i = 0; i < 8; i++) {
      int led_indice = (pos_inicial + i) % NUM_LEDS;
      brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
      tom[led_indice] = 100;
    }
  }

  if (amplitude > FAIXA_B && amplitude <= FAIXA_C) {
    int pos_inicial = random16(NUM_LEDS);
    for (int i = 0; i < 16; i++) {
      int led_indice = (pos_inicial + i) % NUM_LEDS;
      brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
      tom[led_indice] = 200;
    }
  }

  EVERY_N_MILLISECONDS(20) {
    for (int i = 0; i < NUM_LEDS; i++) {
      int led_indice = (i + t) % NUM_LEDS;
      leds[led_indice] = CHSV(tom[led_indice], 255, brilho[led_indice]);
      brilho[led_indice] = scale8(brilho[led_indice], 255 - 10);
    }
    t++;
  }
  FastLED.show();
  delay(20);

  /// Gráfico
  int rangelimit = 4500;
  // int rangelimit = 255;
  Serial.print(0);
  Serial.print(" ");
  Serial.print(rangelimit);
  Serial.print(" ");
  Serial.println(amplitude);
  Serial.println(intensidade);

}

// Função para calcular a amplitude (volume)
int getAmplitude() {
  int signalMax = 0;     // Valor máximo detectado
  int signalMin = 4095;  // Valor mínimo detectado (resolução de 12 bits)

  for (int i = 0; i < SAMPLES; i++) {  // Coleta exatamente SAMPLES amostras
    int sample = analogRead(MIC_PIN);
    if (sample > signalMax) {
      signalMax = sample;  // Atualiza o valor máximo
    }
    if (sample < signalMin) {
      signalMin = sample;  // Atualiza o valor mínimo
    }
  }
  return signalMax - signalMin;  // Amplitude do sinal
}

// Função para calcular a amplitude suavizada
int getSmoothedAmplitude() {
  static int previousAmplitude = 0;
  const float smoothing = 0.3;  // Ajuste este valor (0-1) para mais/menos suavização
  
  int signalMax = 0;
  int signalMin = 4095;
  
  for (int i = 0; i < SAMPLES; i++) {
    int sample = analogRead(MIC_PIN);
    if (sample > signalMax) signalMax = sample;
    if (sample < signalMin) signalMin = sample;
  }
  
  int currentAmplitude = signalMax - signalMin;
  int smoothed = smoothing * currentAmplitude + (1 - smoothing) * previousAmplitude;
  previousAmplitude = smoothed;
  
  return smoothed;
}