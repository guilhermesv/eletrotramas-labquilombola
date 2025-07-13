void efeito_amplitude_ponto(CRGB *leds) {
  int peakToPeak = getAmplitude(); // Calcula a amplitude do sinal

  int sensor = peakToPeak;
  if(sensor < A_RUIDO_LIMITE) {
    sensor = 5;      
  }
  int brilho_max = map(sensor, 0, 3000, 0, 255);
  int hue = mod8(t_1, 255);
  int qtd = map(sensor, 0, 3000, 0, 200);

  for(int i =0; i < qtd; i++) {
    leds[random16(NUM_LEDS)] = CHSV(hue, 255, brilho_max);
    if(random8()>200) {
      leds[random16(NUM_LEDS)] = CHSV(mod8(hue - 50, 255), 255, brilho_max);
    }
  }
   
  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 20);
  }
}
