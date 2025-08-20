// Função para calcular a amplitude (volume)
int getAmplitude() {
  int signalMax = 0;     // Valor máximo detectado
  int signalMin = 4095;  // Valor mínimo detectado (resolução de 12 bits)

  for (int i = 0; i < A_SAMPLES; i++) {  // Coleta exatamente SAMPLES amostras
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
  const float smoothing = 0.6;  // Ajuste este valor (0-1) para mais/menos suavização
  
  int signalMax = 0;
  int signalMin = 4095;
  
  for (int i = 0; i < A_SAMPLES; i++) {
    int sample = analogRead(MIC_PIN);
    if (sample > signalMax) signalMax = sample;
    if (sample < signalMin) signalMin = sample;
  }
  
  int currentAmplitude = signalMax - signalMin;
  int smoothed = smoothing * currentAmplitude + (1 - smoothing) * previousAmplitude;
  previousAmplitude = smoothed;
  
  return smoothed;
}

int sorteia_sentido() {
  return random8(100) > 50 ? 1 : -1;
}