#include <stdio.h>

// Constantes para o tamanho do tabuleiro e dos navios
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio pode ser posicionado dentro dos limites
int validarPosicao(int linha, int coluna, int orientacao) {
    if (orientacao == 0) { // Horizontal
        return (coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    } else if (orientacao == 1) { // Vertical
        return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    }
    return 0;
}

// Função para verificar se há sobreposição com outro navio
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0 && tabuleiro[linha][coluna + i] != 0) return 1;
        if (orientacao == 1 && tabuleiro[linha + i][coluna] != 0) return 1;
    }
    return 0;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0) { // Horizontal
            tabuleiro[linha][coluna + i] = 3;
        } else if (orientacao == 1) { // Vertical
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

int main() {
    // Declaração do tabuleiro e inicialização com água (valor 0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Definindo coordenadas dos navios
    int linhaNavio1 = 2, colunaNavio1 = 3; // Navio horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio vertical

    // Validação e posicionamento do primeiro navio (horizontal)
    if (validarPosicao(linhaNavio1, colunaNavio1, 0) &&
        !verificarSobreposicao(tabuleiro, linhaNavio1, colunaNavio1, 0)) {
        posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, 0);
    } else {
        printf("Erro: não foi possível posicionar o navio 1.\n");
        return 1;
    }

    // Validação e posicionamento do segundo navio (vertical)
    if (validarPosicao(linhaNavio2, colunaNavio2, 1) &&
        !verificarSobreposicao(tabuleiro, linhaNavio2, colunaNavio2, 1)) {
        posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, 1);
    } else {
        printf("Erro: não foi possível posicionar o navio 2.\n");
        return 1;
    }

    // Exibição do tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
