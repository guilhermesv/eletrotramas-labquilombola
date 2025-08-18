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
  // int amplitude = getAmplitude();  
  int amplitude = getSmoothedAmplitude();  

  if(amplitude <= FAIXA_A) {
    processa_faixa(amplitude, FAIXA_A, p_A, cor_faixa_A);
  }
  if(amplitude > FAIXA_A) {
    processa_faixa(amplitude, FAIXA_B, p_B, cor_faixa_B);
  }
  if(amplitude > FAIXA_B) {
    processa_faixa(amplitude, FAIXA_C, p_C, cor_faixa_C);
  }

  EVERY_N_MILLISECONDS(20) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(tom[i], 255, brilho[i]);
      brilho[i] = scale8(brilho[i], 255 - 80);
    }
  }

  EVERY_N_MILLISECONDS(100) {
    t++;
  }

  EVERY_N_SECONDS(8) {
    // p_A = random8(PADROES_QTD-1);
    // p_B = random8(PADROES_QTD-1);
    // p_C = random8(PADROES_QTD-1);

    p_A = (p_A+1) % PADROES_QTD;
    p_B = (p_A+1) % PADROES_QTD;
    p_C = (p_B+1) % PADROES_QTD;

    // cor_faixa_A = (cor_faixa_A + 10)%255;
    // cor_faixa_B = (cor_faixa_B + 1)%255;
    // cor_faixa_C = (cor_faixa_C + 1)%255;
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