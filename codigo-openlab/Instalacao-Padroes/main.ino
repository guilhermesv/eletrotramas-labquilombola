void setup() {
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILIAMPS); 
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  pinMode(MIC_PIN, INPUT);
  Serial.begin(115200);

  p = random8(PADROES_QTD);
  r = random8(REGRAS_QTD);
}

void loop() {
  // MIC
  // int amplitude = getAmplitude();  
  int amplitude = getSmoothedAmplitude();  
  int intensidade = map(amplitude, 0, 3000, 0, 255);
  intensidade = constrain(intensidade, 0, 255);

  // if (amplitude > 0 && amplitude <= FAIXA_A) {
  //   for (int i = 0; i < 48; i++) {
  //     int barra_offset = 0;
  //     for (int i = 0; i < NUM_LEDS; i++) {
  //       if(i % 48 == 0) {
  //         barra_offset++;
  //       }
  //       int padrao_coluna = i % PADRAO_COL_QTD;
  //       int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
  //       if (padroes[1][padrao_linha][padrao_coluna] == regras[0][padrao_coluna] ) {
  //         int led_indice = (i) % NUM_LEDS;
  //         brilho[led_indice] = qadd8(brilho[led_indice], 255);
  //         tom[led_indice] = 180;
  //       }
  //     }
  //   }
  // }

  if (true) { //amplitude > FAIXA_A && amplitude <= FAIXA_B
    for (int i = 48; i < 96; i++) {
      int barra_offset = 0;
      for (int i = 0; i < NUM_LEDS; i++) {
        if(i % 48 == 0) {
          barra_offset++;
        }
        int padrao_coluna = i % PADRAO_COL_QTD;
        int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
        if (padroes[0][padrao_linha][padrao_coluna] == regras[0][padrao_coluna]) {
          int led_indice;
          // if(barra_offset % 2 == 0) {
            led_indice = (i) % NUM_LEDS;
          // } else {
          //   led_indice = (48 - i) % NUM_LEDS;
          // }
          
          brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          tom[led_indice] = 100;
        } else {
          brilho[i] = 0;
        }
      }
    }
  }

  // if (amplitude > FAIXA_B && amplitude <= FAIXA_C) {
  //   for (int i = 96; i < 144; i++) {
  //     int barra_offset = 0;
  //     for (int i = 0; i < NUM_LEDS; i++) {
  //       if(i % 48 == 0) {
  //         barra_offset++;
  //       }
  //       int padrao_coluna = i % PADRAO_COL_QTD;
  //       int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
  //       if (padroes[p][padrao_linha][padrao_coluna] == regras[r][padrao_coluna] ) {
  //         int led_indice = (i) % NUM_LEDS;
  //         brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
  //         tom[led_indice] = 0;
  //       }
  //     }
  //   }
  // }

  

  EVERY_N_MILLISECONDS(20) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(tom[i], 255, brilho[i]);
      brilho[i] = scale8(brilho[i], 255 - 50);
    }
    // t++;
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