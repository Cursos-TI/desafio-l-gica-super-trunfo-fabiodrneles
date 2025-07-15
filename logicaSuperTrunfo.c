#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para a constante EOF

// Estrutura para representar uma carta, agora com campos calculados
typedef struct {
    char estado[3];             // Sigla do estado (ex: SP, RJ)
    char codigo[10];            // Código da carta (ex: A01)
    char cidade[50];            // Nome da cidade
    int populacao;              // População da cidade
    float area;                 // Área em km²
    float pib;                  // PIB em bilhões de reais
    int pontos_turisticos;      // Número de pontos turísticos
    // Campos calculados
    float densidade_populacional; // Calculado: populacao / area
    float pib_per_capita;       // Calculado: (pib * 1_000_000_000) / populacao
} Carta;

// Função para limpar o buffer de entrada (essencial após scanf)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Função para ler os dados de uma carta do usuário
void ler_carta(Carta *c, int numero) {
    printf("\n--- CADASTRO DA CARTA %d ---\n", numero);

    printf("Digite a sigla do estado (ex: SP): ");
    scanf(" %2s", c->estado); // Lê até 2 caracteres para a sigla
    limpar_buffer();

    printf("Digite o código da carta (ex: A01): ");
    scanf("%9s", c->codigo);
    limpar_buffer();

    printf("Digite o nome da cidade: ");
    scanf(" %49[^\n]", c->cidade);
    limpar_buffer();

    printf("Digite a população da cidade: ");
    scanf("%d", &c->populacao);
    limpar_buffer();

    printf("Digite a área da cidade (em km²): ");
    scanf("%f", &c->area);
    limpar_buffer();

    printf("Digite o PIB da cidade (em bilhões de reais): ");
    scanf("%f", &c->pib);
    limpar_buffer();

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &c->pontos_turisticos);
    limpar_buffer();
}

// Função para exibir os dados completos de uma carta, incluindo os calculados
void exibir_carta(Carta c, int numero) {
    printf("\n--- DADOS DA CARTA %d ---\n", numero);
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("Nome da Cidade: %s\n", c.cidade);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões de reais\n", c.pib);
    printf("Número de Pontos Turísticos: %d\n", c.pontos_turisticos);
    // Exibe os dados calculados
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidade_populacional);
    printf("PIB per capita: R$ %.2f\n", c.pib_per_capita);
}

// NOVA FUNÇÃO: Compara duas cartas com base em um atributo escolhido
void comparar_cartas(Carta c1, Carta c2, int escolha) {
    float valor1, valor2;
    char atributo_nome[50];
    int c1_vence = 0; // Flag: 1 se c1 vencer, 0 se c2 vencer
    int empate = 0;   // Flag: 1 se houver empate

    // Seleciona os valores e o nome do atributo com base na escolha do usuário
    switch (escolha) {
        case 1:
            strcpy(atributo_nome, "População");
            valor1 = c1.populacao;
            valor2 = c2.populacao;
            if (valor1 > valor2) c1_vence = 1;
            else if (valor1 == valor2) empate = 1;
            break;
        case 2:
            strcpy(atributo_nome, "Área");
            valor1 = c1.area;
            valor2 = c2.area;
            if (valor1 > valor2) c1_vence = 1;
            else if (valor1 == valor2) empate = 1;
            break;
        case 3:
            strcpy(atributo_nome, "PIB");
            valor1 = c1.pib;
            valor2 = c2.pib;
            if (valor1 > valor2) c1_vence = 1;
            else if (valor1 == valor2) empate = 1;
            break;
        case 4:
            strcpy(atributo_nome, "Pontos Turísticos");
            valor1 = c1.pontos_turisticos;
            valor2 = c2.pontos_turisticos;
            if (valor1 > valor2) c1_vence = 1;
            else if (valor1 == valor2) empate = 1;
            break;
        case 5:
            strcpy(atributo_nome, "Densidade Populacional");
            valor1 = c1.densidade_populacional;
            valor2 = c2.densidade_populacional;
            // Caso especial: menor valor vence
            if (valor1 < valor2) c1_vence = 1;
            else if (valor1 == valor2) empate = 1;
            break;
        case 6:
            strcpy(atributo_nome, "PIB per capita");
            valor1 = c1.pib_per_capita;
            valor2 = c2.pib_per_capita;
            if (valor1 > valor2) c1_vence = 1;
            else if (valor1 == valor2) empate = 1;
            break;
        default:
            printf("Opção de comparação inválida!\n");
            return; // Sai da função se a opção for inválida
    }

    // Exibe o resultado da comparação
    printf("\n--- RESULTADO DA COMPARAÇÃO ---\n");
    printf("Atributo: %s\n", atributo_nome);
    if (escolha == 5) {
        printf("(Regra especial: o menor valor vence!)\n");
    }

    printf("Carta 1 (%s): %.2f\n", c1.cidade, valor1);
    printf("Carta 2 (%s): %.2f\n", c2.cidade, valor2);

    if (empate) {
        printf("\nResultado: EMPATE!\n");
    } else if (c1_vence) {
        printf("\nVENCEDOR: Carta 1 - %s (%s)\n", c1.cidade, c1.estado);
    } else {
        printf("\nVENCEDOR: Carta 2 - %s (%s)\n", c2.cidade, c2.estado);
    }
}


int main() {
    Carta carta1, carta2;

    printf("Bem-vindo ao jogo de Super Trunfo de Cidades!\n");
    printf("Você irá cadastrar duas cartas para competir.\n");

    // Cadastro das cartas
    ler_carta(&carta1, 1);
    ler_carta(&carta2, 2);

    // Cálculo dos campos derivados para as duas cartas
    // Garante que a divisão não será por zero
    if (carta1.area > 0) {
        carta1.densidade_populacional = (float)carta1.populacao / carta1.area;
    } else {
        carta1.densidade_populacional = 0;
    }
    if (carta1.populacao > 0) {
        carta1.pib_per_capita = (carta1.pib * 1000000000) / carta1.populacao;
    } else {
        carta1.pib_per_capita = 0;
    }

    if (carta2.area > 0) {
        carta2.densidade_populacional = (float)carta2.populacao / carta2.area;
    } else {
        carta2.densidade_populacional = 0;
    }
    if (carta2.populacao > 0) {
        carta2.pib_per_capita = (carta2.pib * 1000000000) / carta2.populacao;
    } else {
        carta2.pib_per_capita = 0;
    }


    // Exibição das cartas cadastradas com os dados calculados
    printf("\n\n--- CARTAS PRONTAS PARA O DUELO ---");
    exibir_carta(carta1, 1);
    exibir_carta(carta2, 2);

    // Menu para o usuário escolher o atributo de comparação
    printf("\n\n--- HORA DO DUELO! ---\n");
    printf("Escolha o atributo para comparar:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional (menor vence)\n");
    printf("6. PIB per capita\n");
    printf("Digite o número da sua escolha: ");

    int escolha;
    scanf("%d", &escolha);
    limpar_buffer();

    // Chama a função que realiza a comparação e mostra o resultado
    comparar_cartas(carta1, carta2, escolha);

    return 0;
}