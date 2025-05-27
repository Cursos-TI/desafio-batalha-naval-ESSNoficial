#include <stdio.h>

// Constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para exibir o tabuleiro na tela
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se o navio cabe no tabuleiro conforme a orientação
int validarPosicao(int linha, int coluna, int orientacao) {
    switch (orientacao) {
        case 0: return (coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO); // Horizontal
        case 1: return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO); // Vertical
        case 2: return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO); // Diagonal principal
        case 3: return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna - (TAMANHO_NAVIO - 1) >= 0); // Diagonal secundária
        default: return 0;
    }
}

// Verifica se o navio sobrepõe outro
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        switch (orientacao) {
            case 0: c += i; break; // Horizontal
            case 1: l += i; break; // Vertical
            case 2: l += i; c += i; break; // Diagonal principal
            case 3: l += i; c -= i; break; // Diagonal secundária
        }

        if (tabuleiro[l][c] != 0) return 1; // Já tem navio
    }
    return 0;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        switch (orientacao) {
            case 0: c += i; break; // Horizontal
            case 1: l += i; break; // Vertical
            case 2: l += i; c += i; break; // Diagonal principal
            case 3: l += i; c -= i; break; // Diagonal secundária
        }

        tabuleiro[l][c] = 3;
    }
}

int main() {
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas e orientações fixas dos 4 navios
    // Formato: {linha, coluna, orientação}
    int navios[4][3] = {
        {1, 1, 0}, // horizontal
        {4, 6, 1}, // vertical
        {0, 0, 2}, // diagonal principal
        {2, 9, 3}  // diagonal secundária
    };

    // Tentativa de posicionar cada navio
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        int orientacao = navios[i][2];

        if (validarPosicao(linha, coluna, orientacao) &&
            !verificarSobreposicao(tabuleiro, linha, coluna, orientacao)) {
            posicionarNavio(tabuleiro, linha, coluna, orientacao);
        } else {
            printf("Erro: Não foi possível posicionar o navio %d (linha=%d, coluna=%d, orient=%d)\n",
                   i + 1, linha, coluna, orientacao);
        }
    }

    // Exibe o tabuleiro completo
    exibirTabuleiro(tabuleiro);

    return 0;
}
