#include <stdio.h>
#include "pico/stdlib.h"
#include <hardware/pio.h>
#include "hardware/clocks.h"
#include "pico/bootrom.h"
#include "ws2818b.pio.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25   
#define LED_PIN 7

//Definição dos Botões e RGB
#define BUTTON_A 5  // Pino do botão A
#define BUTTON_B 6  // Pino do botão B
#define LED_VERMELHO 13    // Pino do LED Vermelho
#define LED_VERDE 11    // Pino do LED Verde
#define LED_AZUL 12    // Pino do LED Azul

// Definição do indice
int indice = 1;

// Variáveis globais
static volatile uint a = 1;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

//Padrões dos números
int ZERO[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}}
};
int UM[5][5][3] = {
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};
int DOIS[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}}
};

int TRES[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}}
};

int QUATRO[5][5][3] = {
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}}
};

int CINCO[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}}
};

int SEIS[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}}
};

int SETE[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

int OITO[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}}
};

int NOVE[5][5][3] = {
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{255, 0, 0}, {255, 0, 0}, {255,0, 0}, {255, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
    {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}}
};



// Definição de pixel GRB
struct pixel_t {
 uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

// Declaração de funções
void inoutput_init();


void npInit(uint pin);

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);
void npClear();
void npWrite();
int getIndex(int x, int y);
void npSetPattern(int matriz[5][5][3]);
static void gpio_irq_handler(uint gpio, uint32_t events);

int main() {
 // Inicializa entradas e saídas.
 stdio_init_all();
  inoutput_init();

// Configuração da interrupção com callback
 gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
 gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

 // Inicializa matriz de LEDs NeoPixel.
 npInit(LED_PIN);
 npSetPattern(ZERO);  // Exibe o padrão ZERO

 while (true) {
        gpio_put(LED_VERMELHO, true);
        sleep_ms(100);
        gpio_put(LED_VERMELHO, false);
        sleep_ms(100);
 }
}

// Inicializa os leds e botões
void inoutput_init()
{
    //Input
    gpio_init(LED_VERMELHO);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERMELHO, false);
    gpio_put(LED_AZUL, false);
    gpio_put(LED_VERDE, false);

    // Configura os pinos dos botões como entrada
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);  // Ativa o resistor pull-up interno para o botão A

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);  // Ativa o resistor pull-up interno para o botão B
}

static void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    printf("A = %d\n", a);

        // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 200000) // 200 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        printf("Mudanca de Estado do Led. A = %d\n", a);
        a++;                                     // incrementa a variavel de verificação
    

if (gpio_get(BUTTON_A) == 0) {
        if (indice < 11) {
            indice++;
        }
    }

    // Se o botão B for pressionado, decrementa o índice (não abaixo de 0)
    if (gpio_get(BUTTON_B) == 0) {
        if (indice > 0) {
            indice--;
        }
    }
    }
    // Escolha o padrão a ser exibido com base no índice
        switch (indice) {
            case 1:
                npSetPattern(ZERO);  // Exibe o padrão ZERO
                break;
            case 2:
                npSetPattern(UM);  // Exibe o padrão UM
                break;
            case 3:
                npSetPattern(DOIS);  // Exibe o padrão DOIS
                break;
            case 4:
                npSetPattern(TRES);  // Exibe o padrão TRES
                break;
            case 5:
                npSetPattern(QUATRO);  // Exibe o padrão QUATRO
                break;
            case 6:
                npSetPattern(CINCO);  // Exibe o padrão CINCO
                break;
            case 7:
                npSetPattern(SEIS);  // Exibe o padrão SEIS
                break;
            case 8:
                npSetPattern(SETE);  // Exibe o padrão SETE
                break;
            case 9:
                npSetPattern(OITO);  // Exibe o padrão OITO
                break;
            case 10:
                npSetPattern(NOVE);  // Exibe o padrão NOVE
                break;
            default:
                break;
        }
}


/**
* Inicializa a máquina PIO para controle da matriz de LEDs.
*/
void npInit(uint pin) {

 // Cria programa PIO.
 uint offset = pio_add_program(pio0, &ws2818b_program);
 np_pio = pio0;

 // Toma posse de uma máquina PIO.
 sm = pio_claim_unused_sm(np_pio, false);
 if (sm < 0) {
   np_pio = pio1;
   sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
 }

 // Inicia programa na máquina PIO obtida.
 ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

 // Limpa buffer de pixels.
 for (uint i = 0; i < LED_COUNT; ++i) {
   leds[i].R = 0;
   leds[i].G = 0;
   leds[i].B = 0;
 }
}

/**
* Atribui uma cor RGB a um LED.
*/
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
 leds[index].R = r;
 leds[index].G = g;
 leds[index].B = b;
}

/**
* Limpa o buffer de pixels.
*/
void npClear() {
 for (uint i = 0; i < LED_COUNT; ++i)
   npSetLED(i, 0, 0, 0);
}

/**
* Escreve os dados do buffer nos LEDs.
*/
void npWrite() {
 // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
 for (uint i = 0; i < LED_COUNT; ++i) {
   pio_sm_put_blocking(np_pio, sm, leds[i].G);
   pio_sm_put_blocking(np_pio, sm, leds[i].R);
   pio_sm_put_blocking(np_pio, sm, leds[i].B);
 }
}

int getIndex(int x, int y) {
    // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
    // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
    if (y % 2 == 0) {
        return y * 5 + x; // Linha par (esquerda para direita).
    } else {
        return y * 5 + (4 - x); // Linha ímpar (direita para esquerda).
    }
}

/**
 * Função para acender os LEDs com base nas matrizes de desenho.
 * LEDs com valor 1 no vetor serão acesos com a cor especificada.
 */
void npSetPattern(int matriz[5][5][3]) {
    int index = 0; // Índice para mapear a matriz 2D para o vetor linear de LEDs (0 a 24)
int conversao[5][5][3]=
{
    {{matriz[4][4][0],matriz[4][4][1], matriz[4][4][2]},{matriz[4][3][0],matriz[4][3][1], matriz[4][3][2]}, {matriz[4][2][0],matriz[4][2][1], matriz[4][2][2]}, {matriz[4][1][0],matriz[4][1][1], matriz[4][1][2]}, {matriz[4][0][0],matriz[4][0][1], matriz[4][0][2]}},
    {{matriz[3][0][0],matriz[3][0][1], matriz[3][0][2]}, {matriz[3][1][0],matriz[3][1][1], matriz[3][1][2]}, {matriz[3][2][0],matriz[3][2][1], matriz[3][2][2]}, {matriz[3][3][0],matriz[3][3][1], matriz[3][3][2]}, {matriz[3][4][0],matriz[3][4][1], matriz[3][4][2]}},
    {{matriz[2][4][0],matriz[2][4][1], matriz[2][4][2]}, {matriz[2][3][0],matriz[2][3][1], matriz[2][3][2]}, {matriz[2][2][0],matriz[2][2][1], matriz[2][2][2]}, {matriz[2][1][0],matriz[2][1][1], matriz[2][1][2]}, {matriz[2][0][0],matriz[2][0][1], matriz[2][0][2]}},
    {{matriz[1][0][0],matriz[1][0][1], matriz[1][0][2]},{matriz[1][1][0],matriz[1][1][1], matriz[1][1][2]}, {matriz[1][2][0],matriz[1][2][1], matriz[1][2][2]}, {matriz[1][3][0],matriz[1][3][1], matriz[1][3][2]}, {matriz[1][4][0],matriz[1][4][1], matriz[1][4][2]}},
    {{matriz[0][4][0],matriz[0][4][1], matriz[0][4][2]}, {matriz[0][3][0],matriz[0][3][1], matriz[0][3][2]}, {matriz[0][2][0],matriz[0][2][1], matriz[0][2][2]}, {matriz[0][1][0],matriz[0][1][1], matriz[0][1][2]}, {matriz[0][0][0],matriz[0][0][1], matriz[0][0][2]}}
};


    for (int linha = 0; linha < 5; linha++) {
        for (int coluna = 0; coluna < 5; coluna++) {
            int r = conversao[linha][coluna][0]; // Componente R
            int g = conversao[linha][coluna][1]; // Componente G
            int b = conversao[linha][coluna][2]; // Componente B

            // Acende o LED na posição correspondente
            npSetLED(index, r, g, b);
            index++;
        }
    }
    npWrite(); // Envia os dados para a matriz de LEDs
}