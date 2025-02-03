# embarcatech_2025_u4c4_Interrupcoes
# O projeto prático para explorar o uso de interrupções no microcontrolador RP2040, utilizando a placa de desenvolvimento BitDogLab. O objetivo é demonstrar como implementar um sistema responsivo de controle de LEDs e botões, abordando conceitos fundamentais como debouncing e uso de resistores de pull-up internos.

# Objetivos:

1)Entender o princípio de funcionamento e a utilização de interrupções em microcontroladores.
2)Detectar e solucionar o efeito de bouncing em botões por meio de debounce via software.
3)Operar e gerenciar LEDs convencionais e LEDs endereçáveis WS2812.
4)Reforçar o aprendizado sobre a utilização de resistores de pull-up internos em botões de comando.
5)Projetar e implementar um sistema funcional que integre hardware e software.

#Explicação do Funcionamento:

O projeto consiste em uma matriz 5x5 de LEDs WS2812 e um LED RGB, controlados por dois botões. O funcionamento segue as seguintes regras:
1) O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo;
2) Ao pressionar o Botão A incrementa o número exibido na matriz de LEDs;
3) Ao pressionar o Botão B decrementa o número exibido na matriz de LEDs;
4) Os LEDs WS2812 exibem os números de 0 a 9 em formato digital ou criativo.

# Configuração e Implementação

O código foi desenvolvido no VS Code utilizando o Pico SDK.

A simulação foi realizada no Wokwi para validação lógica antes da implementação real.

No BitDogLab, utilizamos um LED RGB nas GPIOs 11, 12 e 13 e os botões A e B nas GPIOs 5 e 6.

Implementamos uma rotina de software debounce para minimizar os efeitos do bouncing dos botões.

# Demonstração Prática
Agora, vou demonstrar o funcionamento do projeto:

Inicialização do sistema: O sistema aguarda a interação do usuário.

Acionamento dos LEDs: O LED RGB pisca e os botões controlam a matriz de LEDs.

Mudança de estado controlada: Cada pressão de botão A ou B altera o número exibido.

Finalização e reinício: O sistema continua operando aguardando novas interações.

# Resultados Obtidos
A implementação do projeto possibilitou a validação dos conceitos estudados, resultando nos seguintes avanços:

1) Foi possível compreender e aplicar corretamente o uso de interrupções em microcontroladores, garantindo uma resposta eficiente aos eventos externos, como o acionamento do botão.

2) O efeito de bouncing nos botões foi identificado e corrigido com sucesso utilizando técnicas de debouncing via software, resultando em leituras estáveis e confiáveis.

3) Os LEDs convencionais e os LEDs endereçáveis WS2812 foram manipulados e controlados conforme esperado, demonstrando o funcionamento adequado tanto na sinalização básica quanto no acionamento sequencial via comunicação digital.

4) O uso de resistores de pull-up internos nos botões de acionamento foi testado e comprovado, garantindo que os sinais de entrada se mantivessem em níveis lógicos corretos e evitando leituras indevidas.

5) O projeto final apresentou um funcionamento estável e eficiente, integrando hardware e software de maneira coesa, reforçando os conceitos adquiridos e proporcionando um aprendizado prático essencial para o desenvolvimento de sistemas embarcados.

# LInk do vídeo: https://drive.google.com/file/d/1NVTF-MDwqoxRQnMoFWwd6ZU2-7fnOzj_/view?usp=sharing

# Encerramento

A realização deste projeto permitiu a compreensão prática do uso de interrupções em microcontroladores, demonstrando sua importância para a eficiência e responsividade dos sistemas embarcados. Além disso, foi possível identificar e mitigar o efeito de bouncing em botões por meio da implementação de técnicas de debouncing via software, garantindo leituras mais precisas dos sinais de entrada.

A manipulação e o controle de LEDs, tanto convencionais quanto endereçáveis WS2812, reforçaram o conhecimento sobre protocolos de comunicação e acionamento de periféricos. Também foi consolidado o entendimento sobre o uso de resistores de pull-up internos, essenciais para o correto funcionamento dos botões de acionamento.

Por fim, a integração entre hardware e software resultou em um projeto funcional, demonstrando a aplicabilidade dos conceitos estudados e proporcionando uma experiência prática valiosa no desenvolvimento de sistemas embarcados.


