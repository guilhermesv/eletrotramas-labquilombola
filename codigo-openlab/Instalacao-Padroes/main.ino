void setup() {
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILIAMPS); 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  pinMode(MIC_PIN, INPUT);
  Serial.begin(115200);

  // p = random8(PADROES_QTD);
  // r = random8(REGRAS_QTD);

  p = 6;
  r = 0;
}

void loop() {
  // MIC
  // int amplitude = getAmplitude();  
  int amplitude = getSmoothedAmplitude();  
  int intensidade = map(amplitude, 0, 3000, 0, 255);
  intensidade = constrain(intensidade, 0, 255);

  if (amplitude > 0 && amplitude <= FAIXA_A) {
    int barra_offset = 0;
    for (int j = 0; j < NUM_LEDS; j+=BAR_LEDS) {
      for(int i = 0; i < BAR_LEDS; i++) {
        int led_indice;
        int padrao_coluna = (i) % PADRAO_COL_QTD;
        int regra_coluna = (i) % REGRAS_TAM;
        int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
        if (padroes[p][padrao_linha][padrao_coluna] == regras[0][regra_coluna] ) {
          tom[led_indice] = 0;
          if(barra_offset % 2 == 0) {
            led_indice = j+i;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          } else {
            led_indice = (j+BAR_LEDS-1)-i;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          }
        }
      }
      barra_offset++;
    }   
  }

  if (amplitude > FAIXA_A && amplitude <= FAIXA_B) {
    int barra_offset = 0;
    for (int j = 0; j < NUM_LEDS; j+=BAR_LEDS) {
      for(int i = 0; i < BAR_LEDS; i++) {
        int led_indice;
        int padrao_coluna = (i) % PADRAO_COL_QTD;
        int regra_coluna = (i) % REGRAS_TAM;
        int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
        if (padroes[(p+1)%PADROES_QTD][padrao_linha][padrao_coluna] == regras[0][regra_coluna] ) {
          tom[led_indice] = 180;
          if(barra_offset % 2 == 0) {
            led_indice = j+i;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          } else {
            led_indice = (j+BAR_LEDS-1)-i;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          }
        }
      }
      barra_offset++;
    }
  }

  if (amplitude > FAIXA_B && amplitude <= FAIXA_C) {
    int barra_offset = 0;
    for (int j = 0; j < NUM_LEDS; j+=BAR_LEDS) {
      for(int i = 0; i < BAR_LEDS; i++) {
        int led_indice;
        int padrao_coluna = (i) % PADRAO_COL_QTD;
        int regra_coluna = (i) % REGRAS_TAM;
        int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
        if (padroes[(p+2)%PADROES_QTD][padrao_linha][padrao_coluna] == regras[0][regra_coluna] ) {
          tom[led_indice] = 100;
          if(barra_offset % 2 == 0) {
            led_indice = j+i;
            brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          } else {
            led_indice = (j+BAR_LEDS-1)-i;
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
    t++;
  }

  EVERY_N_SECONDS(10) {
    // p = random8(PADROES_QTD);
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