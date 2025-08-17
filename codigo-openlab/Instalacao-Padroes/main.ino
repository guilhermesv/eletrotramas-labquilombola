void setup() {
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILIAMPS); 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  pinMode(MIC_PIN, INPUT);
  Serial.begin(115200);

  p_A = random8(PADROES_QTD-1);
  p_B = random8(PADROES_QTD-1);
  p_C = random8(PADROES_QTD-1);
  // r = random8(REGRAS_QTD);
  
  // p = 6;
  r = 0;
}

void loop() {
  // MIC  
  int amplitude = getAmplitude();
  int intensidade = map(amplitude, 0, 3000, 0, 255);
  intensidade = constrain(intensidade, 0, 255);

  if(amplitude <= FAIXA_A) { 
    CRGB cor_atual = ColorFromPalette(pal_faixa_A, cor_faixa_A, intensidade, LINEARBLEND);
    processa_faixa(p_A, cor_atual);
  }
  if(amplitude > FAIXA_B) {
    CRGB cor_atual = ColorFromPalette(pal_faixa_B, cor_faixa_B, intensidade, LINEARBLEND);
    processa_faixa(p_B, cor_atual);
  }
  if(amplitude > FAIXA_C) {
    CRGB cor_atual = ColorFromPalette(pal_faixa_C, cor_faixa_C, intensidade, LINEARBLEND);
    processa_faixa(p_C, cor_atual);
  }

  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 100);
  }

  EVERY_N_MILLISECONDS(50) {
    t = (t + 1) % NUM_LEDS;
  }

  EVERY_N_SECONDS(8) {
    p_A = random8(PADROES_QTD-1);
    p_B = random8(PADROES_QTD-1);
    p_C = random8(PADROES_QTD-1);

    // p_A = (p_A+1) % PADROES_QTD;
    // p_B = (p_A+1) % PADROES_QTD;
    // p_C = (p_B+1) % PADROES_QTD;

    cor_faixa_A = (cor_faixa_A + 1)%255;
    cor_faixa_B = (cor_faixa_B + 1)%255;
    cor_faixa_C = (cor_faixa_C + 1)%255;
  }

  FastLED.show();
  delay(50);

  /// Gráfico
  int rangelimit = 4500;
  Serial.print(0);
  Serial.print(" ");
  Serial.print(rangelimit);
  Serial.print(" ");
  Serial.println(amplitude);
  
}

