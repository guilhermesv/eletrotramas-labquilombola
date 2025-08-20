int getAmplitude() {
  int signalMax = 0;
  int signalMin = 4095;

  for (int i = 0; i < A_SAMPLES; i++) {
    int sample = analogRead(MIC_PIN);
    if (sample > signalMax) {
      signalMax = sample; 
    }
    if (sample < signalMin) {
      signalMin = sample;
    }
  }
  return signalMax - signalMin;
}

void incrementa_tempo() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis_1 >= interval_1) {
    previousMillis_1 = currentMillis;
    t_1++;
    // Serial.print("t_1: ");
    // Serial.println(t_1);
  }

  if (currentMillis - previousMillis_2 >= interval_2) {
    previousMillis_2 = currentMillis;
    t_2++;
    // Serial.print("t_2: ");
    // Serial.println(t_2);
  }

  t_g++;
}

void efeito_proximo() {
  efeito_contador = (efeito_contador + 1)%3;
  if (src_1_ativa) efeito_src_1 = efeito_contador;  // Determine which source array for new pattern
  else efeito_src_2 = efeito_contador;

  src_1_ativa = !src_1_ativa;                           // Swap source array for next time around
}

void efeito_run(uint8_t efeito, CRGB *leds) {
  switch (efeito) {
    case 0:
      efeito_fft(leds);
      break;
    case 1:
      efeito_amplitude_noise(leds);
      break;
    case 2:
      efeito_amplitude_ponto(leds);
      break;
  }
}
