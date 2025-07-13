// Ajustar a escala para todas as esteiras, 
// talvez seja legal uma escala de ruido grande
// Testei a amplitude controlando a saturacao, verificar

void efeito_amplitude_noise(CRGB *leds) {
  int peakToPeak = getAmplitude(); // Calcula a amplitude do sinal

  int sensor = peakToPeak;
  if(sensor < A_RUIDO_LIMITE) {
    sensor = 5;      
  }
  int brilho_max = map(sensor, 0, 3000, 0, 255);
  int hue = mod8(t_1, 255);
  int sat = map(sensor, 0, 3000, 255, 0);

  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 50);
  }

  uint16_t x = 0;
  int scale = 10;
  uint16_t t = millis() / 10;

  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t noise = inoise8(i * scale + x + t);
    if ( noise > A_NOISE_LIMIAR) {
      //  CHSV hsv = rgb2hsv_approximate(leds[i]);
      //  uint8_t brilho_anterior = hsv.v;
      //  uint8_t brilho_novo = add8(brilho_anterior, brilho_max) ;
      //  leds[i] = CHSV(hue, 255, brilho_novo);

      leds[i] = CHSV(hue, 255, brilho_max);
      // leds[i] = CHSV(hue, 255, avg8(noise/4, brilho_max*2));
      // leds[i] = CHSV(hue, sat, avg8(noise, brilho_max));
      // leds[i] = CHSV(hue, 255, qsub8(brilho_max, noise));
    }
  }
}
