void processa_faixa(uint8_t p, uint8_t r, uint8_t g, uint8_t b) {
  for (int j = 0; j < NUM_LEDS; j += BAR_LEDS) {
    int barra_offset = j / BAR_LEDS;
    bool reverso = barra_offset % 2;
    for (int i = 0; i < BAR_LEDS; i++) {
      int led_indice = reverso ? (j + BAR_LEDS - 1) - i : j + i;
      int padrao_coluna = (i) % PADRAO_COL_QTD;
      int padrao_linha = (barra_offset + t) % PADRAO_LIN_QTD;
      if (padroes[p][padrao_linha][padrao_coluna] == regras[0][0]) {
        leds[led_indice] = CRGB(r, g, b);
      }
    }
  }
}