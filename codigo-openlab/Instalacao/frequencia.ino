// TAMBEM SERIA LEGAL QUE A FREQ ADICIONASSE COR, 
// ASSIM, ELA NAO APAGA PEDACOS

void efeito_fft(CRGB *leds) {

  int frequencias_ignorar = 10;
  int frequencias_divisor = 16; // Minimo 2, para ignorar valores negativos
  int amplitude_min = 2000;
  int amplitude_max = 10000;

  // Coleta de amostras
  for (int i = 0; i < F_SAMPLES; i++) {
    unsigned long time = micros();
    vReal[i] = analogRead(MIC_PIN);
    vImag[i] = 0;
    while ((micros() - time) < (1000000 / F_SAMPLING_FREQUENCY)); // Controla a taxa de amostragem
  }

  // Executa a FFT
  FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);
  FFT.compute(FFTDirection::Forward);
  FFT.complexToMagnitude(vReal, vImag, F_SAMPLES);
  
  for (int i = 0; i < NUM_LEDS; i++) {
    // int ledIndex = (i + t_g) % NUM_LEDS; // Com movimento nas frequencias
    int ledIndex = i; // Sem movimento nas frequencias

    int freqIndex = map(i, 0, NUM_LEDS, frequencias_ignorar, F_SAMPLES / frequencias_divisor);
    double amplitude = vReal[freqIndex];
    if (amplitude > amplitude_min) {
      int brightness = map(amplitude, amplitude_min, amplitude_max, 0, 255);
      brightness = constrain(brightness, 0, 255);
      int sat = 255;
      int hue = mod8(t_1, 255);
      leds[ledIndex] = CHSV(hue, sat, brightness);
    }
  }

  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 20);
  }

}