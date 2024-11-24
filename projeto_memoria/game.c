#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"

#define MAX_JOGADORES 10
#define ARQUIVO_RANKING "ranking.bin"

void exibir_menu() {
                printf("**********************************************************************************************************************************\n");
                printf("**                                                                                                                                                                **\n");
                printf("**                                                    BEM-VINDO AO JOGO DA MEMÓRIA                                                    **\n");
                printf("**                                                                                                                                                                **\n");
                printf("**********************************************************************************************************************************\n");
                printf("**                                                                                                                                                                **\n");
                printf("**                                                    SELECIONE UMA OPÇÃO:                                                                                               **\n");
                printf("**                                                                                                                                                                **\n");
                printf("**                                               1. INICIAR JOGO                                                                                                                **\n");
                printf("**                                               2. INSTRUÇÕES                                                                                                                     **\n");
                printf("**                                               3. CRÉDITOS                                                                                                                        **\n");
                printf("**                                               4. RANKING                                                                                                                         **\n");
                printf("**                                               5. SAIR                                                                                                                                    **\n");
                printf("**                                                                                                                                                                **\n");
                printf("**********************************************************************************************************************************\n");
                printf("OPÇÃO SELECIONADA: ");
            }

void exibir_instrucoes() {
    printf("**********************************************************************************************************************************\n");
    printf("**                                                                                                                                                                **\n");
    printf("**                                                    INSTRUÇÕES                                                                                                             **\n");
    printf("**                                                                                                                                                                **\n");
    printf("**********************************************************************************************************************************\n");
    printf("1. Este é um jogo da memória, onde você deve encontrar todos os pares de cartas.\n");
    printf("2. Escolha as cartas pelo seu índice (linha e coluna).\n");
    printf("3. Quando encontrar um par, as cartas permanecem viradas.\n");
    printf("4. O jogo termina quando todos os pares forem encontrados.\n");
    printf("5. Para sair do jogo e voltar ao menu principal, digite 5 5.\n");
    printf("6. Divirta-se e boa sorte!\n");
    printf("**********************************************************************************************************************************\n");
}
            void exibir_creditos() {
                printf("**********************************************************************************************************************************\n");
                printf("**                                                                                                                                                                **\n");
                printf("**                                                    CRÉDITOS                                                                                                                **\n");
                printf("**                                                                                                                                                                **\n");
                printf("**********************************************************************************************************************************\n");
                printf("Desenvolvido por: Sabrina Cristina Dias\n");
                printf("Curso: Engenharia de software\n");
                printf("Instituição: UCB\n");
                printf("Ano: 2024\n");
                printf("**********************************************************************************************************************************\n");
            }

void salvar_estatisticas(jogador_t jogador) {
    FILE *arquivo = fopen(ARQUIVO_RANKING, "ab");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de ranking");
        return;
    }
    estatisticas_t estatisticas;
    strcpy(estatisticas.nome, jogador.nome);
    estatisticas.paresEncontrados = jogador.paresEncontrados;
    estatisticas.tentativas = jogador.tentativas;
    fwrite(&estatisticas, sizeof(estatisticas_t), 1, arquivo);
    fclose(arquivo);
}


void carregar_ranking() {
    FILE *arquivo = fopen(ARQUIVO_RANKING, "rb");
    if (arquivo == NULL) {
        arquivo = fopen(ARQUIVO_RANKING, "wb");
        if (arquivo == NULL) {
            perror("Erro ao criar arquivo de ranking");
            return;
        }
        fclose(arquivo);
        arquivo = fopen(ARQUIVO_RANKING, "rb");
        if (arquivo == NULL) {
            perror("Erro ao abrir arquivo de ranking");
            return;
        }
    }
    estatisticas_t estatisticas;
    int count = 0;
    printf("----------------------------------------------\n");
    printf("| Ranking dos Jogadores                      |\n");
    printf("----------------------------------------------\n");
    while (fread(&estatisticas, sizeof(estatisticas_t), 1, arquivo) == 1 && count < MAX_JOGADORES) {
        printf("| %2d. Nome: %s, Pares Encontrados: %2d, Tentativas: %2d |\n", count + 1, estatisticas.nome, estatisticas.paresEncontrados, estatisticas.tentativas);
        count++;
    }
    printf("----------------------------------------------\n");
    fclose(arquivo);
}

void exibir_ranking() {
    printf("-------------------------------------------------\n");
    printf("|                                                 |\n");
    printf("|                     RANKING                     |\n");
    printf("|                                                 |\n");
    printf("-------------------------------------------------\n");
    carregar_ranking();
    printf("-------------------------------------------------\n");
}

#include <unistd.h>

void print_current_directory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Diretório atual: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}

tabuleiro_t* carregar_fase(const char *nome_arquivo, int linhas, int colunas) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo da fase");
        return NULL;
    }

    tabuleiro_t *tabuleiro = (tabuleiro_t *)malloc(sizeof(tabuleiro_t));
    tabuleiro->linhas = linhas;
    tabuleiro->colunas = colunas;
    tabuleiro->cartas = (carta_t **)malloc(linhas * sizeof(carta_t *));
    for (int i = 0; i < linhas; i++) {
        tabuleiro->cartas[i] = (carta_t *)malloc(colunas * sizeof(carta_t));
        for (int j = 0; j < colunas; j++) {
            fscanf(arquivo, " %c", &tabuleiro->cartas[i][j].simbolo);
            tabuleiro->cartas[i][j].virada = 0;
        }
    }
    fclose(arquivo);
    return tabuleiro;
}



    void liberar_tabuleiro(tabuleiro_t *tabuleiro) {
        for (int i = 0; i < tabuleiro->linhas; i++) {
            free(tabuleiro->cartas[i]);
        }
        free(tabuleiro->cartas);
        free(tabuleiro);
    }

    void exibir_tabuleiro(tabuleiro_t *tabuleiro) {
        printf("Tabuleiro:\n");
        for (int i = 0; i < tabuleiro->linhas; i++) {
            for (int j = 0; j < tabuleiro->colunas; j++) {
                if (tabuleiro->cartas[i][j].virada) {
                    printf(" %c ", tabuleiro->cartas[i][j].simbolo);
                } else {
                    printf(" * ");
                }
            }
            printf("\n");
        }
    }

    int virar_carta(tabuleiro_t *tabuleiro, int linha, int coluna) {
        if (linha < 0 || linha >= tabuleiro->linhas || coluna < 0 || coluna >= tabuleiro->colunas) {
            return 0;
        }
        if (tabuleiro->cartas[linha][coluna].virada) {
            return 0;
        }
        tabuleiro->cartas[linha][coluna].virada = 1;
        return 1;
    }

    void iniciar_jogo() {
        char *fases[] = {"fase1.txt", "fase2.txt", "fase3.txt", "fase4.txt", "fase5.txt"};
        int linhas[] = {2, 3, 3, 4, 4};
        int colunas[] = {2, 3, 3, 4, 4};
        int total_fases = 5;
        jogador_t jogador;
        printf("Digite seu nome: ");
        scanf("%s", jogador.nome);
        jogador.paresEncontrados = 0;
        jogador.tentativas = 0;

        for (int fase_atual = 0; fase_atual < total_fases; fase_atual++) {
            tabuleiro_t *tabuleiro = carregar_fase(fases[fase_atual], linhas[fase_atual], colunas[fase_atual]);
            if (tabuleiro == NULL) {
                printf("Erro ao carregar a fase %d\n", fase_atual + 1);
                continue;
            }
            printf("Iniciando fase %d\n", fase_atual + 1);

            while (jogador.paresEncontrados < (tabuleiro->linhas * tabuleiro->colunas) / 2) {
                exibir_tabuleiro(tabuleiro);
                printf("Digite as coordenadas da primeira carta (linha coluna): ");
                int linha1, coluna1;
                scanf("%d %d", &linha1, &coluna1);
                if (linha1 == 5 && coluna1 == 5) {
                    printf("Voltando ao menu principal...\n");
                    liberar_tabuleiro(tabuleiro);
                    return;
                }
                while (!virar_carta(tabuleiro, linha1, coluna1)) {
                    printf("Carta inválida! Digite novamente: ");
                    scanf("%d %d", &linha1, &coluna1);
                    if (linha1 == 5 && coluna1 == 5) {
                        printf("Voltando ao menu principal...\n");
                        liberar_tabuleiro(tabuleiro);
                        return;
                    }
                }

                exibir_tabuleiro(tabuleiro);
                printf("Digite as coordenadas da segunda carta (linha coluna): ");
                int linha2, coluna2;
                scanf("%d %d", &linha2, &coluna2);
                if (linha2 == 5 && coluna2 == 5) {
                    printf("Voltando ao menu principal...\n");
                    liberar_tabuleiro(tabuleiro);
                    return;
                }
                while (!virar_carta(tabuleiro, linha2, coluna2)) {
                    printf("Carta inválida! Digite novamente: ");
                    scanf("%d %d", &linha2, &coluna2);
                    if (linha2 == 5 && coluna2 == 5) {
                        printf("Voltando ao menu principal...\n");
                        liberar_tabuleiro(tabuleiro);
                        return;
                    }
                }

                if (tabuleiro->cartas[linha1][coluna1].simbolo == tabuleiro->cartas[linha2][coluna2].simbolo) {
                    printf("Par encontrado!\n");
                    jogador.paresEncontrados++;
                    salvar_estatisticas(jogador);
                } else {
                    printf("Não é um par!\n");
                    tabuleiro->cartas[linha1][coluna1].virada = 0;
                    tabuleiro->cartas[linha2][coluna2].virada = 0;
                }
                jogador.tentativas++;
            }
            printf("Você completou a fase %d em %d tentativas!\n", fase_atual + 1, jogador.tentativas);
            salvar_estatisticas(jogador); 
            liberar_tabuleiro(tabuleiro);
        }
    }
