#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define MAX 5

char letras[] = {'I', 'O', 'T', 'L'};
int tamanho = sizeof(letras) / sizeof(letras[0]);

int id = 0;

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca peca[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

typedef struct {
    Peca peca[MAX];
    int topo;
} Pilha;

Peca retornaPecaAleatoria() {
    int indice = rand() % tamanho;
    Peca p = {letras[indice], id};
    return p;
}

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
}

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void inserirFila(Fila *fila, Peca peca) {
    peca.id = id;
    id++;
    fila->peca[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % MAX;
    fila->total++;
}

void inserirPilha(Pilha *pilha, Peca peca) {
    pilha->topo++;
    pilha->peca[pilha->topo] = peca;
}

void removerFila(Fila *fila, Peca *peca) {
    *peca = fila->peca[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX;
    fila->total--;
    inserirFila(fila, retornaPecaAleatoria());
}

void removerPilha(Pilha *pilha, Peca *peca) {
    *peca = pilha->peca[pilha->topo];
    pilha->topo--;
}

void mostrarFila(Fila *fila) {
    printf("Fila de peças: ");
    for (int i = 0, idx = fila->inicio; i < fila->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c,%d] ", fila->peca[idx].tipo, fila->peca[idx].id);
    }
    printf("\n");
}

void mostrarPilha(Pilha *pilha) {
    printf("Pilha de peças: ");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%c,%d] ", pilha->peca[i].tipo, pilha->peca[i].id);
    }
    printf("\n");
}

int main() {
    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    Pilha pilha;
    inicializarPilha(&pilha);

    for (int i = 0; i < MAX; i++) {
        inserirFila(&fila, retornaPecaAleatoria());
    }

    mostrarFila(&fila);
    mostrarPilha(&pilha);

    int opcao;
    do {
        printf("Menu:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Jogar peça reservada\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                Peca pecaRemovida;

                if (filaVazia(&fila)) {
                    printf("Fila vazia! Não é possível remover peça.\n");
                    break;
                }

                removerFila(&fila, &pecaRemovida);
                printf("Peça jogada: [%c,%d]\n", pecaRemovida.tipo, pecaRemovida.id);

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);

                break;
            case 2:
                Peca pecaReservada;

                if (pilhaCheia(&pilha)) {
                    printf("Pilha cheia! Não é possível reservar peça.\n");
                    break;
                }

                removerFila(&fila, &pecaReservada);
                inserirPilha(&pilha, pecaReservada);
                printf("Peça reservada: [%c,%d]\n", pecaReservada.tipo, pecaReservada.id);

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            case 3:
                Peca pecaUsada;

                if (pilhaVazia(&pilha)) {
                    printf("Pilha vazia! Não é possível usar peça.\n");
                    break;
                }

                removerPilha(&pilha, &pecaUsada);
                printf("Peça usada: [%c,%d]\n", pecaUsada.tipo, pecaUsada.id);

                printf("\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);



    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}
