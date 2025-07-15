#include <FastLED.h>

// DEFINICOES LED
#define LED_PIN 4 
#define NUM_LEDS 1200

CRGB leds[NUM_LEDS];

// DEFINICOES MIC
#define MIC_PIN     34      // Pino do microfone
#define SAMPLES     256     // Número de amostras para analisar

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
}

void loop() {
  // MIC  
  // Ajuste gráfico
  int rangelimit = 4500;
  Serial.print(0);
  Serial.print(" ");
  Serial.print(rangelimit);
  Serial.print(" ");

  int peakToPeak = getAmplitude(); // Calcula a amplitude do sinal
  Serial.println(peakToPeak);
  // Serial.print("Amplitude: ");
  // Serial.println(peakToPeak);
  delay(100);

  // LED
  int led_acesos = map(peakToPeak, 0, 3000, 0, NUM_LEDS);
  for(int i = 0; i < led_acesos; i++) {
    leds[i] = CRGB(5, 0, 0);
  }

  // int led_aceso = map(peakToPeak, 0, 3000, 0, 255);
  // leds[led_aceso] = CRGB(10, 0, 0);

  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 10);
  }
  FastLED.show();

}

// Função para calcular a amplitude (volume)
int getAmplitude() {
  int signalMax = 0;  // Valor máximo detectado
  int signalMin = 4095; // Valor mínimo detectado (resolução de 12 bits)

  for (int i = 0; i < SAMPLES; i++) { // Coleta exatamente SAMPLES amostras
    int sample = analogRead(MIC_PIN);
    if (sample > signalMax) {
      signalMax = sample; // Atualiza o valor máximo
    }
    if (sample < signalMin) {
      signalMin = sample; // Atualiza o valor mínimo
    }
  }
  return signalMax - signalMin; // Amplitude do sinal
}





