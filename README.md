Participei de 2024 a 2025 da primeira edição da residência Labquilombola promovida pela Maranha que tem como base a troca de saberes entre mestras quilombolas e artistas. Este repositório abriga todos os códigos dos experimentos e obra que desenvolvi durante a residência.

Mais informações sobre a residência pode ser lida no site: [https://www.instagram.com/labquilombola/](https://www.instagram.com/labquilombola/).

As informações nesse respositório estão bem objetivas, escrevi um longo texto detalhando vários aspectos técnicos em meu blog, caso queira algo mais aprofundado recomendo a leitura do texto disponível no link: https://guilhermevieira.info/2026/03/residencia-labquilombola-ideias-e-processos/#descritivo 

# Este repositório

A organização desse repositório é feita em 2 pastas baseada na minha organização pessoal durante a residência e nos dois momentos da residência, Hacklab e Openlab:
- codigo-hacklab: aqui você irá encontrar códigos preliminares e experimentos desenvolvido antes e durante a estadia no território do Quilombo da Fazenda.
- codigo-openlab: todas as iterações e testes realizados para compor a obra Eletrotramas.

# Eletrotramas

Eletrotramas é a obra interativa desenvolvida para a residência, que foi composta por um conjunto de esteiras tramadas com fibras de taboa e fitas de LEDs enderaçáveis, 2 caixas com microntroladores e microfone que captavam o som de um tambor e criavam padrões nas fitas de acordo com o volume dessa interação.

![Instalação](/doc/Foto-Instala%C3%A7%C3%A3o.jpg)

# Lista de Componentes

**Unidade de controle** (quantidade pra 2 unidades de controle)

- 2 Placa DOIT ESP32 - ESP32-WROOM-32D
- 2 Módulo microfone max9814
- 2 Fonte Hi-Link 3.3v
- 2 Jack P10 Stereo para PCI
- 2 Plugue P10 Stereo
- 2 Chave HH - SS12F23 (2 posições, 90°)
- 2 Borne Kre 2 vias
- 2 Plugue tomada 2 pinos
- 4 terminal pré-isolado agulha 1,5 a 2,5mm
- 6 m Cabo PP Flexível  2 x 0,75mm 
- 2 Placa De Fenolite 5x10cm Perfurada Pcb Ilhada
- 2 caixas de acrílico cortadas no laser

**Esteira** (quantidade pra fazer 8 esteiras e 36 caneletas de Led)

- 36 Perfil plástico U 12x12 mm em PS (poliestireno) de 80 cm 
- 6 m de cabo 3 vias para fita LED
- 24 m Cabo PP Flexível  3 x 0,5mm
- Conexão entre as esteiras e controlador
- 6 m Cabo PP Flexível  2 x 0,75mm 
- Conexão da fonte para a esteira
- 48 conectores Wago 3 pólos
- 30 m de fita de LED endereçável WS2812 de 5V
- 2 Fonte de Alimentação 5v 10a

# Circuito - Esteira

As esteiras possuem uma estrutura simples, 3 entradas e 3 saídas que foram feitas com os conectores WAGO para facilitar a montagem e conexões entre as fitas de cada canaleta feitas com fio e solda convencional isoladas com termoretrátil.

![Circuito - Esteira](/doc/Circuito-Esteira.jpg)

# Circuito - Controlador

A base do controlador é um ESP32 que recebe o áudio do microfone MAX9814, processa e envia as informações para a fita de LED. Foi adicionado ao circuito uma fonte para isolar a alimentação do controle das fitas de LED e também uma chave HH para alternar a alimentação do controle entre a fonte e o USB. O controlador se conecta as esteiras por um cabo P2 que leva o sinal de dados e também o GND para equalizar a alimentação da fonte interna com a da das fitas de LED.

![Circuito - Controle](/doc/Circuito-Controle.png)

# Circuito - Instalação

Na instalação foram criados 2 conjuntos, cada um deles com sua própria fonte, controlador e 4 esteiras. No circuito algums detalhes importantes de ressaltar:

- Para manter a establidade do sistema e evitar ruídos no sinal enviado pelo controlador é necessário conectar o GND da fonte de 5V com o do controlador.
- Para fitas de LED de 5V a cada 5m é necessário reforçar a alimentação para evitar queda de tensão. 

![Circuito - Instalação](/doc/Circuito-Instala%C3%A7%C3%A3o.jpg)

# Observações

- Fitas de LED consomem muita energia, caso queira experimentar esse código, faça pequenos testes antes de utilizar uma grande quantidade de LED.
- Recomendo a leitura do texto sobre alimentação da biblioteca FastLED, disponível no link: https://github.com/FastLED/FastLED/blob/master/cookbook/core-concepts/power.md






