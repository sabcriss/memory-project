#include <stdio.h>
#include "game.h"

int main() {
    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                iniciar_jogo();
                break;
            case 2:
                exibir_instrucoes();
                break;
            case 3:
                exibir_creditos();
                break;
            case 4:
                exibir_ranking();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);
    return 0;
}
