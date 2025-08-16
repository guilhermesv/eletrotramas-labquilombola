void processa_faixa(uint8_t p, uint8_t r, uint8_t g, uint8_t b) {
  int barra_offset = 0;
  for (int j = 0; j < NUM_LEDS; j += BAR_LEDS) {
    for (int i = 0; i < BAR_LEDS; i++) {
      int led_indice;
      int padrao_coluna = (i) % PADRAO_COL_QTD;
      int regra_coluna = (i) % REGRAS_TAM;
      int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
      if (padroes[p][padrao_linha][padrao_coluna] == regras[0][regra_coluna]) {
        if (barra_offset % 2 == 0) {
          led_indice = j + i;
          // brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          leds[led_indice] = CRGB(r, g, b);
        } else {
          led_indice = (j + BAR_LEDS - 1) - i;
          // brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
          leds[led_indice] = CRGB(r, g, b);
        }
      }
    }
    barra_offset++;
  }
}


// void processa_faixa(int amplitude, int faixa, uint8_t p, uint8_t &cor) {
//   int barra_offset = 0;
//     int intensidade = map(amplitude, 0, faixa, 0, 255);
//     intensidade = constrain(intensidade, 0, 255);
//     for (int j = 0; j < NUM_LEDS; j+=BAR_LEDS) {
//       for(int i = 0; i < BAR_LEDS; i++) {
//         int led_indice;
//         int padrao_coluna = (i) % PADRAO_COL_QTD;
//         int regra_coluna = (i) % REGRAS_TAM;
//         int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
//         if (padroes[p][padrao_linha][padrao_coluna] == regras[0][regra_coluna] ) {
//           CRGB cor_atual = CHSV(cor, 255, 255);
//           CHSV cor_atual_HSV = rgb2hsv_approximate(cor_atual);
//           if(barra_offset % 2 == 0) {
//             led_indice = j+i;
//             tom[led_indice] = cor_atual_HSV.hue;
//             brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
//           } else {
//             led_indice = (j+BAR_LEDS-1)-i;
//             tom[led_indice] = cor_atual_HSV.hue;
//             brilho[led_indice] = qadd8(brilho[led_indice], intensidade);
//           }
//         }
//       }
//       barra_offset++;
//     }
// }