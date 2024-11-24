#ifndef GAME_H
#define GAME_H

typedef struct {
    char simbolo;
    int virada;
} carta_t;

typedef struct {
    carta_t **cartas;
    int linhas;
    int colunas;
} tabuleiro_t;

typedef struct {
    char nome[100];
    int paresEncontrados;
    int tentativas;
} jogador_t;

typedef struct {
    char nome[100];
    int paresEncontrados;
    int tentativas;
} estatisticas_t;

void exibir_menu();
void exibir_instrucoes();
void exibir_creditos();
void exibir_ranking();
tabuleiro_t* inicializar_tabuleiro(int linhas, int colunas);
void liberar_tabuleiro(tabuleiro_t *tabuleiro);
void exibir_tabuleiro(tabuleiro_t *tabuleiro);
int virar_carta(tabuleiro_t *tabuleiro, int linha, int coluna);
void iniciar_jogo();
void salvar_estatisticas(jogador_t jogador);
void carregar_ranking();
tabuleiro_t* carregar_fase(const char *nome_arquivo, int linhas, int colunas); 

#endif 
