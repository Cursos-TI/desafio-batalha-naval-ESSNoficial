#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs()

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define HABILIDADE 5

// Função para inicializar uma matriz com zeros
void inicializarMatriz(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            matriz[i][j] = 0;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar um navio horizontal, vertical ou diagonal
int posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        int l = linha, c = coluna;

        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'E') { l += i; c -= i; }

        // Verificar limites
        if (l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] != 0)
            return 0;

    }

    // Inserir após validação
    for (int i = 0; i < 3; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'E') { l += i; c -= i; }

        tabuleiro[l][c] = NAVIO;
    }

    return 1;
}

// Função para criar matriz de habilidade Cone
void criarCone(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i >= j - centro && i >= centro - j)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para criar matriz de habilidade Cruz
void criarCruz(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == centro || j == centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para criar matriz de habilidade Octaedro (losango)
void criarOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Função para aplicar a matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linhaTab = origemLinha - offset + i;
            int colunaTab = origemColuna - offset + j;

            // Verificar se está dentro do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                if (matriz[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == 0) {
                    tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarMatriz(tabuleiro);

    // Posicionamento de 4 navios
    posicionarNavio(tabuleiro, 0, 0, 'H'); // Horizontal
    posicionarNavio(tabuleiro, 2, 2, 'V'); // Vertical
    posicionarNavio(tabuleiro, 5, 0, 'D'); // Diagonal principal
    posicionarNavio(tabuleiro, 5, 9, 'E'); // Diagonal invertida

    // Matrizes de habilidade
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades ao tabuleiro em pontos específicos
    aplicarHabilidade(tabuleiro, cone, 7, 2);       // Cone em (7,2)
    aplicarHabilidade(tabuleiro, cruz, 2, 7);       // Cruz em (2,7)
    aplicarHabilidade(tabuleiro, octaedro, 5, 5);   // Octaedro em (5,5)

    // Exibir tabuleiro final
    printf("Tabuleiro com navios (3) e habilidades (5):\n\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
