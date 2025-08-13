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

  if (amplitude > 0 && amplitude <= FAIXA_A) {
    int barra_offset = 0;
    int intensidade = map(amplitude, 0, FAIXA_A, 0, 255);
    intensidade = constrain(intensidade, 0, 255);
    for (int j = 0; j < NUM_LEDS; j+=BAR_LEDS) {
      for(int i = 0; i < BAR_LEDS; i++) {
        int led_indice;
        int padrao_coluna = (i) % PADRAO_COL_QTD;
        int regra_coluna = (i) % REGRAS_TAM;
        int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
        if (padroes[p_A][padrao_linha][padrao_coluna] == regras[0][regra_coluna] ) {
          CRGB cor_atual = ColorFromPalette(pal_faixa_A, cor_faixa_A, 255, LINEARBLEND);
          CHSV cor_atual_HSV = rgb2hsv_approximate(cor_atual);
          if(barra_offset % 2 == 0) {
            led_indice = j+i;
            tom[led_indice] = cor_atual_HSV.hue;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          } else {
            led_indice = (j+BAR_LEDS-1)-i;
            tom[led_indice] = cor_atual_HSV.hue;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          }
        }
      }
      barra_offset++;
    }   
  }

  if (amplitude > FAIXA_A && amplitude <= FAIXA_B) {
    int barra_offset = 0;
    int intensidade = map(amplitude, FAIXA_A, FAIXA_B, 0, 255);
    intensidade = constrain(intensidade, 0, 255);
    for (int j = 0; j < NUM_LEDS; j+=BAR_LEDS) {
      for(int i = 0; i < BAR_LEDS; i++) {
        int led_indice;
        int padrao_coluna = (i) % PADRAO_COL_QTD;
        int regra_coluna = (i) % REGRAS_TAM;
        int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
        if (padroes[p_B][padrao_linha][padrao_coluna] == regras[0][regra_coluna] ) {
          CRGB cor_atual = ColorFromPalette(pal_faixa_B, cor_faixa_B, 255, LINEARBLEND);
          CHSV cor_atual_HSV = rgb2hsv_approximate(cor_atual);       
          if(barra_offset % 2 == 0) {
            led_indice = j+i;
            tom[led_indice] = cor_atual_HSV.hue;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          } else {
            led_indice = (j+BAR_LEDS-1)-i;
            tom[led_indice] = cor_atual_HSV.hue;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          }
        }
      }
      barra_offset++;
    }
  }

  if (amplitude > FAIXA_B && amplitude <= FAIXA_C) {
    int barra_offset = 0;
    int intensidade = map(amplitude, FAIXA_B, FAIXA_C, 0, 255);
    intensidade = constrain(intensidade, 0, 255);
    for (int j = 0; j < NUM_LEDS; j+=BAR_LEDS) {
      for(int i = 0; i < BAR_LEDS; i++) {
        int led_indice;
        int padrao_coluna = (i) % PADRAO_COL_QTD;
        int regra_coluna = (i) % REGRAS_TAM;
        int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
        if (padroes[p_C][padrao_linha][padrao_coluna] == regras[0][regra_coluna] ) {
          CRGB cor_atual = ColorFromPalette(pal_faixa_C, cor_faixa_C, 255, LINEARBLEND);
          CHSV cor_atual_HSV = rgb2hsv_approximate(cor_atual);
          if(barra_offset % 2 == 0) {
            led_indice = j+i;
            tom[led_indice] = cor_atual_HSV.hue;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          } else {
            led_indice = (j+BAR_LEDS-1)-i;
            tom[led_indice] = cor_atual_HSV.hue;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          }
        }
      }
      barra_offset++;
    }
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
    p_A = random8(PADROES_QTD-1);
    p_B = random8(PADROES_QTD-1);
    p_C = random8(PADROES_QTD-1);

    // p_A = (p_A+1) % PADROES_QTD;
    // p_B = (p_A+1) % PADROES_QTD;
    // p_C = (p_B+1) % PADROES_QTD;

  }

  EVERY_N_SECONDS(1) {
    cor_faixa_A = (cor_faixa_A + 1)%255;
    cor_faixa_B = (cor_faixa_B + 1)%255;
    cor_faixa_C = (cor_faixa_C + 1)%255;
  }

  FastLED.show();
  delay(50);

  /// Gráfico
  int rangelimit = 4500;
  // Serial.print(0);
  // Serial.print(" ");
  // Serial.print(rangelimit);
  // Serial.print(" ");
  // Serial.println(amplitude);
  Serial.println(cor_faixa_A);
}