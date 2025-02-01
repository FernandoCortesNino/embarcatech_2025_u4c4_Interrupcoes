# embarcatech_2025_u4c4_Interrupcoes
# Oprojeto prático para explorar o uso de interrupções no microcontrolador RP2040, utilizando a placa de desenvolvimento BitDogLab. O objetivo é demonstrar como implementar um sistema responsivo de controle de LEDs e botões, abordando conceitos fundamentais como debouncing e uso de resistores de pull-up internos.

#Explicação do Funcionamento:
#O projeto consiste em uma matriz 5x5 de LEDs WS2812 e um LED RGB, controlados por dois botões. O funcionamento segue as seguintes regras:
1) O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo;
2) O Botão A incrementa o número exibido na matriz de LEDs;
3) O Botão B decrementa o número exibido na matriz de LEDs;
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

Mudança de estado controlada: Cada pressão de botão altera o número exibido.

Finalização e reinício: O sistema continua operando aguardando novas interações.

# Resultados Obtidos
Os testes demonstraram que:

O controle de LEDs e botões via interrupções funcionou corretamente.

O debounce garantiu acionamentos precisos, evitando ruídos.

A implementação no BitDogLab permitiu validar a simulação de forma eficiente.

# Encerramento
Portanto, concluímos a apresentação do projeto, explicando os conceitos, demonstrando o funcionamento e validando os resultados obtidos. O código-fonte e as instruções detalhadas estarão disponíveis em um repositório do GitHub. Muito obrigado por assistir!
