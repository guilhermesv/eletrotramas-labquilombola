void setup() {
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILIAMPS); 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  pinMode(MIC_PIN, INPUT);
  Serial.begin(115200);

  p_A = 0;
  p_B = 0;
  p_C = 0;
  
  // p_A_sentido = sorteia_sentido();
  // p_B_sentido = sorteia_sentido();
  // p_C_sentido = sorteia_sentido();
  // r = random8(REGRAS_QTD);
  
  // p = 6;
  r = 0;

  fill_solid( leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(5000);
}

void loop() {

  // MIC  
  int amplitude = getSmoothedAmplitude();
  int intensidade = map(amplitude, RUIDO, 3000, RUIDO_BRILHO, 255);
  intensidade = constrain(intensidade, RUIDO_BRILHO, 255);

  CRGB cor_atual_A = ColorFromPalette(pal_faixa_A, cor, RUIDO_BRILHO, LINEARBLEND);
  processa_faixa(p_A, cor_atual_A, p_A_sentido);
  if(amplitude >= RUIDO) {
    // intensidade = map(amplitude, RUIDO, FAIXA_A, RUIDO_BRILHO, 255);
    // intensidade = constrain(intensidade, RUIDO_BRILHO, 255);
    CRGB cor_atual_A = ColorFromPalette(pal_faixa_A, cor, intensidade, LINEARBLEND);
    processa_faixa(p_A, cor_atual_A, p_A_sentido);
  }
  if(amplitude > FAIXA_B) {
    CRGB cor_atual_B = ColorFromPalette(pal_faixa_B, cor, intensidade, LINEARBLEND);
    processa_faixa(p_B, cor_atual_B, p_B_sentido);
  }
  if(amplitude > FAIXA_C) {
    CRGB cor_atual_C = ColorFromPalette(pal_faixa_C, cor, intensidade, LINEARBLEND);
    processa_faixa(p_C, cor_atual_C, p_C_sentido);
  }

  EVERY_N_MILLISECONDS(20) {
    fadeToBlackBy(leds, NUM_LEDS, 70);
  }

  EVERY_N_MILLISECONDS(50) {
    t = (t + 1) % NUM_LEDS;
  }

  EVERY_N_SECONDS(8) {
    p_A = random(PADROES_QTD-1);
    p_B = random(PADROES_QTD-1);
    p_C = random(PADROES_QTD-1);

    // p_A_sentido = sorteia_sentido();
    // p_B_sentido = sorteia_sentido();
    // p_C_sentido = sorteia_sentido();

    // p_A = (p_A+1) % PADROES_QTD;
    // p_B = (p_A+1) % PADROES_QTD;
    // p_C = (p_B+1) % PADROES_QTD;

    // Serial.println("cor");
    // Serial.println(cor);

    // Serial.println("padrao");
    // Serial.print(p_A);
    // Serial.print(" ");
    // Serial.print(p_B);
    // Serial.print(" ");
    // Serial.println(p_C);

    // Serial.print("SRAM livre: ");
    // Serial.print(ESP.getFreeHeap());
    // Serial.println(" bytes");
    // Serial.println("-----------------");
  }

  EVERY_N_SECONDS(42) { // 42 Gera um ciclo de aprox. 3h
    cor = (cor + 1)%255;
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

